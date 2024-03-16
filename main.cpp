#include <iostream>
#include <fstream>

 using namespace std;

class User
{
public:
    string user_name;
    string user_password;
    int user_balance;
    int user_id;
    int user_type;
    User user(){};
};

int main() {
    cout << "Welcome to the Yagiz Bank" << endl;
    cout << "1 - Login" << endl;
    cout << "2 - Register" << endl;

    User user;
    int choice;
    int file_location = 0;
    bool logged_in = false;
    string user_name;
    string user_password;
    string temp_user_name;
    string temp_password;
    string token;
    bool is_valid = true;

    ifstream database_ifs("database.txt");
    ofstream database_ofs("database.txt",ios_base::app);
    ofstream tempFile("temp.txt",ios_base::app);
    if(!database_ifs.is_open() && !database_ofs.is_open())
    {
        cout << "File is corrupted";
        return 0;
    }
    cout << "Please enter your choice : ";
    cin >> choice;
    do {
        switch (choice) {
            case 0:
                if(!logged_in)
                {
                    cout << "MAIN MENU" << endl;
                    cout << "1 - Login" << endl;
                    cout << "2 - Register" << endl;
                    cout << "Please enter your choice : ";
                    cin >> choice;
                }else
                {
                    cout << "------------------------------" << endl;
                    cout << "WELCOME TO OUR BANK" << endl;
                    cout << "------------------------------" << endl;
                    cout << "Current balance : " << endl;
                    cout << "1 - Deposit" << endl;
                    cout << "2 - Withdraw" << endl;
                    cout << "3 - Exit" << endl;
                    cout << "Please enter your choice : ";
                    cin >> choice;
                    int current_line_number = 0;
                    string money;
                    switch (choice) {
                        default:
                            break;
                        case 1:
                            cout << "Pleae enter money amount that you want to deposit : ";
                            cin >> money;
                            database_ifs.clear();
                            database_ifs.seekg(0,std::ios::beg);
                            while(!database_ifs.eof())
                            {
                                current_line_number++;
                                database_ifs >> token;
                                if(file_location == current_line_number)
                                {
                                    database_ifs >> token;
                                    tempFile << stoi(money) + stoi(token);
                                }else{
                                    tempFile << token;
                                }
                                tempFile << endl;
                            }
                            choice = 0;
                            remove("database.txt");
                            rename("temp.txt","database.txt");
                            cout << "Thanks for your deposit." << endl;
                            break;
                        case 2:
                            cout << "Pleae enter money amount that you want to deposit : ";
                            cin >> money;
                            database_ifs.clear();
                            database_ifs.seekg(0,std::ios::beg);
                            while(!database_ifs.eof())
                            {
                                current_line_number++;
                                database_ifs >> token;
                                if(file_location == current_line_number)
                                {
                                    database_ifs >> token;
                                    if(-stoi(money) + stoi(token) >= 0)
                                    {
                                        tempFile << -stoi(money) + stoi(token);
                                    }else{
                                        cout << "Not enough balance. Please try again.";
                                        choice = 2;
                                        break;
                                    }
                                }else{
                                    tempFile << token;
                                }
                                tempFile << endl;
                            }
                            choice = 0;
                            remove("database.txt");
                            rename("temp.txt","database.txt");
                            cout << "Thanks for your withdraw." << endl;
                            break;
                        case 3:
                            logged_in = false;
                            choice = 0;
                            break;
                    }
                }
                break;
            case 1:
                cout << "Enter your user name : ";
                cin >> user_name;
                cout << "Enter your password : ";
                cin >> user_password;
                database_ifs.clear();
                database_ifs.seekg(0,std::ios::beg);
                while(!database_ifs.eof())
                {
                    database_ifs >> temp_user_name;
                    database_ifs >> temp_password;
                    database_ifs >> token;
                    file_location += 3;
                    if(temp_user_name == user_name && user_password == temp_password)
                    {
                        cout << "You logged in." << endl;
                        logged_in = true;
                        choice = 0;
                        user.user_name = user_name;
                        user.user_password = user_password;
                        user.user_id = file_location;
                        user.user_type = 0;
                        break;
                    }
                }
                cout << "Wrong id or password."<<endl;
                choice = 0;
                break;
            case 2:
                cout << "Enter your user name : ";
                cin >> user_name;
                cout << "Enter your password : ";
                cin >> user_password;
                database_ifs.clear();
                database_ifs.seekg(0,std::ios::beg);
                while(!database_ifs.eof())
                {
                    database_ifs >> temp_user_name;
                    database_ifs >> temp_password;
                    database_ifs >> token;
                    if(temp_user_name == user_name)
                    {
                        user_name = "";
                        user_password = "";
                        cout << "There is already account that associated with that username." << endl;
                        is_valid = false;
                        break;
                    }
                }
                if(is_valid)
                {
                    database_ofs << user_name;
                    database_ofs << endl;
                    database_ofs << user_password;
                    database_ofs << endl;
                    database_ofs << 0;
                    database_ofs << endl;
                    choice = 0;
                    cout << "Thanks for your registiration." << endl;
                    cout << "------------------------------" << endl;
                    cout << "WELCOME TO OUR BANK" << endl;
                    cout << "------------------------------" << endl;
                    break;
                }else{
                    choice = 0;
                    break;
                }
            default:
                continue;
        }

    }while(choice != -1);


    database_ofs.close();
    database_ifs.close();
    return 0;
}