#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
double purse=500000;

struct property {
    int id;
    char types[50];
    char location[100];
    double price;
};
struct property p;

void display() {
    FILE *fp;
    fp = fopen("techpro.txt", "rb");
    if (fp == NULL) {
        printf("Error: File not found or cannot be opened\n");
        return;
    }
    printf("\n---Available Property details are as follows:----\n");
    printf("ID\tTYPE\t\tLOCATION\tPRICE\n"); 
    while (fread(&p, sizeof(p), 1, fp) == 1) {
        printf("%-6d\t%-10s\t%-8s\t%-6lf\n", p.id, p.types, p.location, p.price);
    }
    fclose(fp);
}
void display1() {
    FILE *fp;
    fp = fopen("user.txt", "rb");
    if (fp == NULL) {
        printf("Error: File not found or cannot be opened\n");
        return;
    }
    printf("\n---Owning property details are as follows:----\n");
    printf("ID\tTYPE\t\tLOCATION\tPRICE\n"); 
    while (fread(&p, sizeof(p), 1, fp) == 1) {
        printf("%-6d\t%-10s\t%-8s\t%-6lf\n", p.id, p.types, p.location, p.price);
    }
    fclose(fp);
}

void buyProperty() {
    FILE *fp, *ft, *userFile;
    int pid;
    unsigned flag = 0;
     int purchased = 0;

    fp = fopen("techpro.txt", "rb");
    if (fp == NULL) {
        printf("Error: File not found or cannot be opened\n");
        return;
    }
    display(); 

    printf("Enter Property id you want to buy: ");
    scanf("%d", &pid);

    ft = fopen("temp.txt", "wb");
    userFile = fopen("user.txt", "ab+"); 

    while (fread(&p, sizeof(p), 1, fp) == 1) {
        if (pid == p.id) {
            if (purse >= p.price) {
                flag = 1;
                purse -= p.price; 
                fwrite(&p, sizeof(p), 1, userFile); 
                purchased=1;
            } else {
                flag=2;
                printf("Not enough puse value to buy this Property.\n");
            }
        } else {
            fwrite(&p, sizeof(p), 1, ft);
        }
    }

    if (flag == 0) {
        printf("Error: No such record found\n");
    } else if (flag==1){
        printf("Successfully bought the Property\n");
    }
        fclose(fp);
    fclose(ft);
    fclose(userFile);

        if (purchased==1) {
        remove("techpro.txt");
        rename("temp.txt", "techpro.txt");
    }
    
}

void sellProperty() {
    FILE *userFile, *fp, *tempFile;
    int pid;
    unsigned flag = 0;

    userFile = fopen("user.txt", "rb");
    if (userFile == NULL) {
        printf("Error: User file not found or cannot be opened\n");
        return;
    }

    display1(); 

    printf("Enter the Property id you want to sell: ");
    scanf("%d", &pid);

    fp = fopen("techpro.txt", "ab+"); 
    tempFile = fopen("temp.txt", "wb");

    while (fread(&p, sizeof(p), 1, userFile) == 1) {
        if (pid == p.id) {
            flag = 1;
            purse += p.price;
            fwrite(&p, sizeof(p), 1, fp);
        } else {
            fwrite(&p, sizeof(p), 1, tempFile);
        }
    }

    if (flag == 0) {
        printf("Error: Property not found in your list\n");
    } else {
        printf("Property sold successfully\n");
    }

    fclose(userFile);
    fclose(tempFile);
    fclose(fp);
    remove("user.txt");
    rename("temp.txt", "user.txt");
}


void add_Property() {
    FILE *fp;
    fp = fopen("techpro.txt", "ab+");
    if (fp == NULL) {
        printf("Error: File not found or cannot be opened\n");
        return;
    }
    printf("Enter new Property details:\n");
    printf("Enter Property ID: ");
    scanf("%d", &p.id);
    fflush(stdin);
    printf("Enter Property type: ");
    scanf("%s", p.types);
    printf("Enter Property location: ");
    scanf("%s", p.location); 
    printf("Enter Property price: ");
    scanf("%lf", &p.price); 
    fwrite(&p, sizeof(p), 1, fp);
    printf("Property inserted successfully\n");
    fclose(fp);
}


void search() {
    FILE *fp;
    char loc[100]; 
    int flag = 0;
    fp = fopen("techpro.txt", "rb");
    if (fp == NULL) {
        printf("Error: File not found or cannot be opened\n");
        return;
    }
    printf("Enter location where you want to search for properties: ");
    scanf("%s", loc); 
    printf("\n---Available Property details in %s are as follows:---\n", loc);
    printf("ID\tTYPE\t\tLOCATION\tPRICE\n");
    while (fread(&p, sizeof(p), 1, fp) > 0) {
        if (strcasecmp(p.location, loc) == 0) { 
            flag = 1;
            printf("%-6d\t%-10s\t%-8s\t%-6lf\n", p.id, p.types, p.location, p.price);
        }
    }
    if (flag == 0) {
        printf("\n No Properties available in %s\n", loc);
    }
    fclose(fp);
}

void remove_Property() {
    FILE *fp, *ft;
    int pid;
    unsigned flag = 0;
    fp = fopen("techpro.txt", "rb");
    if (fp == NULL) {
        printf("Error: File not found or cannot be opened\n");
        return;
    }
    display();
    printf("Enter the Property id you want to delete: ");
    scanf("%d", &pid);
    ft = fopen("temp.txt", "wb"); 
    while (fread(&p, sizeof(p), 1, fp) == 1) {
        if (pid == p.id) {
            flag=1;
        } else {
            fwrite(&p, sizeof(p), 1, ft);
        }
    }
    if (flag == 0) {
        printf("Error: No such record found\n");
    }
    else{
        printf("Successfully deleted the Property\n");
    }
    fclose(fp);
    fclose(ft);
    remove("techpro.txt");
    rename("temp.txt", "techpro.txt");
}

void update() {
    FILE *fp;
    int pid;
    int flag = 0;
    fp = fopen("techpro.txt", "r+b"); 
    if (fp == NULL) {
        printf("Error: File not found or cannot be opened\n");
        return;
    }
    printf("Enter property id which you want to update: ");
    scanf("%d", &pid);
    while (fread(&p, sizeof(p), 1, fp) > 0 && flag == 0) {
        if (p.id == pid) {
            flag = 1;
            printf("Enter updated property details: \n");
            printf("Enter updated property ID: ");
            scanf("%d", &p.id);
            fflush(stdin);
            printf("Enter updated property type: ");
            scanf("%s", p.types);
            printf("Enter updated property location: ");
            scanf("%s", p.location);
            printf("Enter updated property price: ");
            scanf("%lf", &p.price);
            fseek(fp, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, fp);
            printf("Property updated successfully\n");
        }
    }
    if (flag == 0) {
        printf("Error: Property not found\n");
    }
    fclose(fp);
}

int main() {
    int ch,log,pwd;
    printf("Enter 0 for admin login OR Enter 1 for user login : \n");
    scanf("%d",&log);
    if(log==0){
        printf("Enter admin password:  \n");
        fflush(stdin);
        scanf("%d",&pwd);
        if(pwd!=1234){
            printf("Wrong password!!!!!\n");
            main();
        }
        else{
            printf("login successfull_-_-_\n");
            while (ch != 7) {
        printf("********************************************************\n");
        printf("\t\tReal Estate Advisor\n");
        printf("********************************************************\n");
        printf("----------------------ADMIN MENU------------------------\n");
        printf("\t\t1. Display Property\n");
        printf("\t\t2. Add Property\n");
        printf("\t\t3. Remove Property\n");
        printf("\t\t4. Search Property\n");
        printf("\t\t5. Modify Property\n");
        printf("\t\t6. Switch to user page\n");
        printf("\t\t7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                display();
                break;
            case 2:
                add_Property();
                break;
            case 3:
                remove_Property(); 
                break;
            case 4:
                search();
                break;
            case 5:
                update();
                break;
            case 6: main();
                break;
            case 7:
                printf("Quitting!!!!!\n");
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
        }
    }
        }
    }
    else if(log==1){
      while (ch != 7) {
        printf("********************************************************\n");
        printf("\t\tReal Estate Advisor\n");
        printf("********************************************************\n");
        printf("-----------------------USER MENU------------------------\n");
        printf("\t\t1. Display all Properties\n");
        printf("\t\t2. Search Property\n");
        printf("\t\t3. Buy Property\n");
        printf("\t\t4. Sell Property\n");
        printf("\t\t5. Display owning Properties\n");
        printf("\t\t6. Switch to admin page\n");
        printf("\t\t7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                display();
                break;
            case 2:
                search();
                break;
            case 3:buyProperty();
                break;
            case 4:sellProperty();
                 break;
            case 5:display1();
                break;
            case 6:main();
                break;
            case 7:
                printf("Quitting!!!!!\n");
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
            }
        }
    }
    else{
        printf("Invalid input!!!!\n");
        main();
    }
    
    return 0;
}
