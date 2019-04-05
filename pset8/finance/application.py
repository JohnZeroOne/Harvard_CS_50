import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp

import werkzeug
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # get the user's stock portfolio
    stocks = db.execute("SELECT * FROM portfolio WHERE id = :id",
                        id=session["user_id"])

    # calculate the grand total
    grandtotal = 0

    # append API data to stocks dict
    # user has stocks
    if stocks:
        # iterate over each stock
        for stock in stocks:
            # get current stock values
            api = lookup(stock["symbol"])
            # add api values to dict
            stock.update(api)
            # add total to dict
            total = stock["shares"] * stock["price"]
            stock["total"] = total
            grandtotal += stock["total"]

    # get the user's cash
    cash = db.execute("SELECT cash FROM users WHERE id = :id",
                      id=session["user_id"])
    # get cash from inner dict
    cash = cash[0]["cash"]
    # convert cash into dict
    cash = {"symbol": "CASH", "total": cash}
    # add cash to grandtotal
    grandtotal += cash["total"]
    # convert grandtotal into dict
    grandtotal = {"total": grandtotal}
    # add cash to list
    stocks.append(cash)
    # add grandtotal to list
    stocks.append(grandtotal)

    # show user their portfolio
    return render_template("index.html", stocks=stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # get symbol info. from API via user input
        symbol = lookup(request.form.get("symbol"))
        # check symbol is valid
        if not symbol:
            return apology("Symbol not valid.", 400)

        # check that user entered shares
        if not request.form.get("shares") or not request.form.get("shares").isdigit():
            return apology("Please enter shares.")

        # get shares from user
        shares = int(request.form.get("shares"))

        # check that shares are valid
        if shares <= 0:
            return apology("Shares must be greater than 0.")
        try:
            assert isinstance(shares, int)
        except:
            return apology("Shares must be a positive integer")

        # check user has enough money
        cash = db.execute("SELECT cash FROM users WHERE id = :id",
                          id=session["user_id"])
        # validate cash
        if not cash:
            return apology("Cash error")
        # get the value of cash from the list
        cash = cash[0]["cash"]
        # calculate cost of purchase
        cost = symbol["price"] * shares
        # user doesn't have enough money
        if cost > float(cash):
            return apology("Not enough money.", 400)
        # set transaction type
        type = "buy"
        # not 100% sure how to do this yet
        # check is user has already bought stocks in this company
        rows = db.execute("SELECT * FROM portfolio WHERE id = :id AND symbol = :symbol",
                          id=session["user_id"], symbol=symbol["symbol"])
        # rows is not empty
        if rows:
            for row in rows:
                # user already has stocks in this company
                if row["symbol"] in symbol["symbol"]:
                    # update current entry in portfolio
                    db.execute("UPDATE portfolio SET shares = shares + :shares WHERE id = :id AND symbol = :symbol",
                               shares=shares, id=session["user_id"], symbol=symbol["symbol"])
                    break
        # user doesn't have existing stocks with this company
        else:
            # add shares to portfolio
            db.execute("INSERT INTO portfolio (id,symbol,shares) VALUES(:id, :symbol, :shares)",
                       id=session["user_id"], symbol=symbol["symbol"], shares=shares)

        # add transaction to the record
        db.execute("INSERT INTO transactions (id,type,symbol,shares,price) VALUES(:id, :type, :symbol, :shares, :price)",
                   id=session["user_id"], type=type, symbol=symbol["symbol"], shares=shares, price=symbol["price"])

        # update user's cash
        db.execute("UPDATE users SET cash = cash - :cost WHERE id = :id",
                   cost=cost, id=session["user_id"])

        # flash message
        flash("Stocks purchased")

        # Submit the user’s input via POST to /buy.
        return redirect("/")

    else:

        # give user form to buy stocks
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""

    # User reached route via GET
    if request.method == "GET":
        # get the username from form
        username = request.form.get("username")
        # check if username already exists
        userdb = db.execute("SELECT * FROM users WHERE username = :username",
                            username=username)
        # print("USERDB: ", userdb)

        # check validity of username
        if username and userdb:
            if len(username) > 0 and not userdb:
                # username is valid
                return jsonify(True)
        else:
            # flash message
            flash(u'Invalid username provided', 'error')

            # username is invalid
            return jsonify(False)
    else:
        # user reach form erroneously
        return apology("Error")


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Change user password."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure password & confirmation were submitted
        if not request.form.get("password" or not request.form.get("confirmation")):
            return apology("Must provide password & confirmation", 400)

        # check passwords match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match.", 400)

        # hash the password so it is stored safely in the database
        hash = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)

        # insert username, password into db
        result = db.execute("UPDATE users SET hash = :hash WHERE id = :id",
                            hash=hash, id=session["user_id"])
        # username already exists in db
        if not result:
            return apology("Password error.", 400)

        # flash message
        flash("Password changed")

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("password.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # get data from transaction table
    transactions = db.execute("SELECT * FROM transactions WHERE id = :id",
                              id=session["user_id"])
    # Show user transaction history
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # flash message
        flash("Logged in")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # flash message
    flash("Logged out")

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # get symbol info. from API
        quote = lookup(request.form.get("symbol"))

        # check quote is valid
        if quote:
            # flash message
            flash("Quote")
            # display stock quote
            return render_template("quoted.html", quote=quote)
        else:
            return apology("Symbol entry invalid", 400)

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Must provide username", 400)

        # Ensure password & confirmation was submitted
        elif not request.form.get("password" or not request.form.get("confirmation")):
            return apology("Must provide password & confirmation", 400)

        # check passwords match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match.", 400)

        # hash the password so it is stored safely in the database
        hash = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)

        # insert username, password into db
        result = db.execute("INSERT INTO users(username,hash) VALUES(:username, :hash)",
                            username=request.form.get("username"), hash=hash)
        # username already exists in db
        if not result:
            return apology("Username taken.", 400)

        # store session to log in automatically
        session["user_id"] = result

        # flash message
        flash("Registered")

        # Redirect user to home page
        return redirect("/")

    else:
        # Show user registration form
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # get symbol info. from API via user input
        symbol = lookup(request.form.get("symbol"))
        # check symbol is valid
        if not symbol:
            return apology("Symbol not valid.", 400)

        # try to remove stock from users portfolio
        remove = db.execute("UPDATE portfolio SET shares = shares - :shares WHERE id = :id AND symbol = :symbol AND shares >= :shares",
                            shares=request.form.get("shares"), id=session["user_id"], symbol=request.form.get("symbol"))
        select = db.execute("SELECT * FROM portfolio WHERE id = :id AND symbol = :symbol",
                            id=session["user_id"], symbol=request.form.get("symbol"))
        # delete entries with no shares
        if select[0]["shares"] == 0:
            delete = db.execute("DELETE FROM portfolio WHERE shares = 0 AND id = :id",
                                id=session["user_id"])
        # check that shares were removed before giving user cash
        if remove:
            # get current share value
            cshares = lookup(request.form.get("symbol"))
            price = float(cshares["price"])
            shares = int(request.form.get("shares"))
            price *= shares
            # update users cash
            cash = db.execute("UPDATE users SET cash = cash + :price WHERE id = :id",
                              price=price, id=session["user_id"])
        else:
            # user tried to sell more shares than they possess
            return apology("You don't own these shares")

        # user didn't enter symbol or shares or they don't exist in db
        if not (request.form.get("symbol") or
                request.form.get("shares") or
                cshares or
                cash):
            return apology("Symbol or shares not valid.")

        # set type of transaction
        type = "sell"

        # add transaction to the record
        db.execute("INSERT INTO transactions (id,type,symbol,shares,price) VALUES(:id, :type, :symbol, :shares, :price)",
                   id=session["user_id"], type=type, symbol=symbol["symbol"], shares=shares, price=symbol["price"])

        # flash message
        flash("Stocks sold")

        # redirect to index page
        return redirect("/")
    else:
        # get user stocks
        stocks = db.execute("SELECT * FROM portfolio WHERE id = :id",
                            id=session["user_id"])
        # give user form to sell stocks
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
