#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include <stdbool.h>
#include<stdarg.h>

#define MAXSURNAME 11 //max length for surname

//Structure of contacts

typedef struct
{
    char surname[MAXSURNAME];
    char name[MAXSURNAME];
    int phone_number;
} the_contact_t;

//List of commands

enum commands {
    Exit,
    Enter_date,
    Edit_date,
    Delete_date,
    Find_date,
    Print_date,
    Call_phone_number
};

//For calls

enum call {
    Exit_from_call,
    Call_by_name,
    Call_by_number
};

//Finding menu

enum finding {
    Exit_from_finding,
    Find_by_surname,
    Find_by_phone_number
};

//Read contacts from file function

the_contact_t* read_from_file(uint64_t* size_array)
{
    the_contact_t* a;
    FILE *f = NULL;
    f = fopen("contacts.txt", "rb");
    if (f == NULL)
    {
        printf("Not opened\n");
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    size_t size_f = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size_f % sizeof(the_contact_t) != 0)
    {
        return NULL;
    }
    *size_array = (size_f / sizeof(the_contact_t));
    a = (the_contact_t*)malloc(sizeof(the_contact_t)*(*size_array));
    fread(a, sizeof(the_contact_t), *size_array, f);
    fclose(f);
    return a;
}

//Write contacts to file

the_contact_t* write_to_file(the_contact_t* a, uint64_t* size_array)
{
    FILE *f = NULL;
    f = fopen("contacts.txt", "w+b");
    if (f == NULL)
    {
        printf("Not opened\n");
        return NULL;
    }
    fwrite(a, sizeof(the_contact_t), *size_array, f);
    fclose(f);
    return a;
}

//Enter personal data of contacts

the_contact_t* enter_date(the_contact_t* a, uint64_t* size_array) {
    if (a == NULL) {
        (*size_array) = 1;
        a = (the_contact_t*)malloc(sizeof(the_contact_t)*(*size_array));
    }
    else
    {
        (*size_array)++;
        a = realloc(a, sizeof(the_contact_t)*(*size_array));
    }
        printf("Enter Surname\n");
        scanf("%s", a[(*size_array)-1].surname);
        printf("Enter Name\n");
        scanf("%s", a[(*size_array)-1].name);
        printf("Enter phone number\n");
        scanf("%d", &a[(*size_array)-1].phone_number);
//		fwrite(&a[i], 1, sizeof(the_contact_t), f);
    return a;
}

//Print contacts data function

void* print_struct(the_contact_t* a, uint64_t* size_array)
{
    //sorting matrix by alphabet

    for (int n = 0; n < 10; n++)
    {
        the_contact_t buffer;
        int64_t counter = 0;
        for (int i = 0; i < *size_array-1; i++)
        {
            if (strcmp(a[i].surname, a[i + 1].surname) > 0)
            {
                buffer = a[i];
                a[i] = a[i + 1];
                a[i + 1] = buffer;
                counter++;
            }
        }
        if (counter == 0)
        {
            break;
        }
    }

    //Print matrix

    for (int index = 0; index < *size_array; index++)
    {
        printf("Contact is  %s %s\n", a[index].surname, a[index].name);
        printf("Position in list is %d\n", index);
        printf("Phone number is %d\n", a[index].phone_number);
    }
}

//Edit contact information

void* edit_contact(the_contact_t* a, uint64_t* size_array)
{
    int position = -1;
    printf("Enter number of position for edit\n");
    scanf("%d", &position);
    printf("Enter Surname\n");
    scanf("%s", a[position].surname);
    printf("Enter Name\n");
    scanf("%s", a[position].name);
    printf("Enter Phone number\n");
    scanf("%d", &a[position].phone_number);
}

//Finding contact

the_contact_t* find_contact(the_contact_t* a, uint64_t* size_array)
{
    int64_t input_for_finding = -1;
    do {
        printf("Press 0 for exit\n");
        printf("Press 1 for finding by surname\n");
        printf("Press 2 for finding by phone number\n");
        scanf("%li", &input_for_finding);
        char find_surname[MAXSURNAME];
        uint64_t find_phone = 0;
        switch(input_for_finding) {
            case Find_by_surname:
                printf("Enter Surname\n");
                scanf("%s", find_surname);
//                gets(find_surname);
                for (int index = 0; index < *size_array; index++)
                {
                    if (strcmp(a[index].surname, find_surname) == 0)
                    {
                        printf("Contact is  %s %s", a[index].surname, a[index].name);
                        printf("Position in list is %d\n", index);
                        printf("Phone number is %d\n", a[index].phone_number);
                    }
                }
                break;
            case Find_by_phone_number:
                printf("Enter Phone number\n");
                scanf("%lu", &find_phone);
                for (int index = 0; index < *size_array; index++)
                {
                    if (find_phone == a[index].phone_number)
                    {
                        printf("Contact is  %s %s", a[index].surname, a[index].surname);
                        printf("Position in list is %d\n", index);
                        printf("Phone number is %d\n", a[index].phone_number);
                    }
                }
                break;
            default:
                printf("Repeat your choice");
                break;
        }
    }while(input_for_finding != Exit_from_finding);
}

//For delete contact

the_contact_t* delete_date(the_contact_t* a, uint64_t* size_array) {
    printf("Enter position of contacts for delete\n");
    int64_t position = -1;
    scanf("%li", &position);

    for(position; position < (*size_array)-1; position++)
        {
            a[position] = a[position+1];
        }
    (*size_array)--;
    a = realloc(a, sizeof(the_contact_t)*(*size_array));
    return a;
}

void* call_number(the_contact_t* a, uint64_t* size_array)
{
    int64_t input_for_call = -1;
    do {
        printf("Press 0 for Exit from call\n");
        printf("Press 1 for Call by surname\n");
        printf("Press 2 for Call by phone number\n");
        scanf("%li", &input_for_call);
        char find_surname[MAXSURNAME];
        uint64_t find_phone = 0;
        switch (input_for_call)
        {
            case Call_by_name:
                printf("Enter Surname\n");
                scanf("%s", find_surname);
//                gets(find_surname);
                for (int index = 0; index < *size_array; index++)
                {
                    if (strcmp(a[index].surname, find_surname) == 0)
                    {
                        printf("Call to number %d\n", a[index].phone_number);
                        system("pause");
                    }
                }
                break;
            case Call_by_number:
                printf("Enter Phone number\n");
                scanf("%lu", &find_phone);
                printf("Call to number %lu\n", find_phone);
                system("pause");
                bool total = false;
                for (int index = 0; index < *size_array; index++)
                {
                    if (find_phone == a[index].phone_number)
                    {
                        total = true;
                        break;
                    }
                }
                if (!total)
                {
                    enter_date(a, &size_array);
                }
                break;
            default:
                printf("Repeat your choice");
                break;
        }
    }while(input_for_call != Exit_from_call);
}

int main()
{
    the_contact_t* a = NULL;
    uint64_t size_array = 0;
    a = read_from_file(&size_array);
    uint64_t input = 0;
    do {
        printf("Press 0 for Exit\n");
        printf("Press 1 for Enter data\n");
        printf("Press 2 for Edit data\n");
        printf("Press 3 for Delete data\n");
        printf("Press 4 for Find data\n");
        printf("Press 5 for Print data\n");
        printf("Press 6 for Call\n");
        scanf("%lu", &input);
        switch (input) {
            case Enter_date:
                a = enter_date(a, &size_array);
                break;
            case Edit_date:
                edit_contact(a, &size_array);
                break;
            case Delete_date:
                a = delete_date(a, &size_array);
                break;
            case Find_date:
                find_contact(a, &size_array);
                break;
            case Print_date:
                printf("Base yours contacts is:\n");
                print_struct(a, &size_array);
                break;
            case Call_phone_number:
                call_number(a, &size_array);
                break;
            default:
                printf("Repeat your choice");
                break;
        }
    } while (input != Exit);
    write_to_file(a, &size_array);
    return 0;
}