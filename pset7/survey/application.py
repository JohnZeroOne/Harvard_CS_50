import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():

    # get values from form submission
    name = request.form.get("name")
    house = request.form.get("house")
    quidditch = request.form.get("quidditch")

    # validate a form's submission
    if not name or not house or not quidditch:
        return render_template("error.html", message="You must enter: name, house, quidditch position.")

    # write user entries to csv row
    with open("survey.csv", "a") as file:
        # need to write header line here
        writer = csv.DictWriter(file, fieldnames=["name", "house", "quidditch"])
        writer.writerow({"name": name, "house": house, "quidditch": quidditch})

    # redirect flask to sheet
    return redirect("/sheet")


@app.route("/sheet", methods=["GET"])
def get_sheet():

    # read past submissions from survey.csv
    with open("survey.csv", "r") as file:
        reader = csv.DictReader(file)
        students = list(reader)

    # display submissions in an HTML table, new template
    return render_template("sheet.html", students=students)