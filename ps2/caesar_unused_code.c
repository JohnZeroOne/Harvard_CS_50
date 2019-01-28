// Check that argv[1] only contains numbers by iterating its elements
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            for (int j = 0, numbers = "0123456789") m = strlen(numbers); j < m; j++)
            {
                if (argv[1][i] < "0" || argv[1][i] > "9")
            {
                printf("bugtest\n");
                printf("Usage: ./caesar key\n");
                return -1;
            }
            }
            
            //printf("%c\n", argv[1][i]);
            

/*
            if (argv[1][i] < "0" || argv[1][i] > "9")
            printf("bugtest\n");
            printf("Usage: ./caesar key\n");
            return -1;
            //printf("%c\n", argv[1][i]);
            */
