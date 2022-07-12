#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
using namespace std;
class Customer
{
public:
    char First_name[31];
    char Last_name[31];
    char Father_name[31];
    char Pass_code[31];
    char call_num[31];
    bool delleted;
    int id;
};
Customer alpha;
class Time
{
public:
    int day;
    int mon;
    int year;
    void get_tiem(void)
    {
        Time A;
        cout << "\nEnter year : ";
        cin >> A.year;
        cout << "\nEnter mon : ";
        cin >> A.mon;
        cout << "\nEnter day : ";
        cin >> A.day;
    }
};
Time alpha_t;
class House
{
public:
    char loc[51];
    char kind[5];
    int price;
    int masahat;
    int rooms;
    int Id;
    bool delleted;
};
class Request
{
public:
    Customer A;
    House B;
    int ID;
    bool accepting;
    bool cancel;
    Time t;
};
void show_re(Request A)
{
    cout << "\n-------------------\n";
    cout << "\nCustomer " << A.A.First_name << " " << A.A.Last_name << " whit id : " << A.A.id << " want house whit id " << A.B.Id;
    cout << "\nDate to request : " << A.t.year << " / " << A.t.mon << " / " << A.t.day;
    cout << "\nId request is : " << A.ID;
    cout << "\n-------------------\n";
    return;
}
void get_time(void)
{
    Time A;
    cout << "\nEnter year : ";
    cin >> A.year;
    cout << "\nEnter mon : ";
    cin >> A.mon;
    cout << "\nEnter day : ";
    cin >> A.day;
    alpha_t = A;
}
bool tiem_handel(Time D, Time C)
{
    if (D.year <= C.year)
    {
        if ((D.mon <= C.mon) && (D.year == C.year))
        {
            if ((D.mon == C.mon) && (D.day <= C.day))
            {
                return true;
            }
        }
        return true;
    }
    return false;
}
void time_search(void)
{
    Time G, B;
    cout << "\nEnter Origin time ";
    G.get_tiem();
    cout << "\nEnter desteny time ";
    B.get_tiem();
    if (!tiem_handel(G, B))
    {
        cout << "\nWrong entering time  ";
        return;
    }
    ifstream F;
    Request A;
    F.open("report.dat", ios::in | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again\n";
        return;
    }
    F.read((char *)&A, sizeof(Request));
    while (!F.eof())
    {
        if ((tiem_handel(G, A.t)) && tiem_handel(A.t, B))
        {
            show_re(A);
        }
        F.read((char *)&A, sizeof(Request));
    }
}
class Admin
{
public:
    string username;
    string pasword;
    void set(string nam, string pas)
    {
        username = nam;
        pasword = pas;
        return;
    }
};
int filesize(string filename)
{
    ifstream X;
    int size;
    X.open(filename, ios::in);
    if (!X.is_open())
    {
        return 0;
    }
    else
    {
        X.seekg(0, ios::end);
        size = X.tellg();
        X.close();
        return size;
    }
}
bool check_pas(Admin admin_name)
{
    string pas, nam;
    cout << "Admin please enter username : ";
    cin >> nam;
    cout << "Admin please enter pasword : ";
    cin >> pas;
    if ((pas.compare(admin_name.pasword) == 0) && (nam.compare(admin_name.username)) == 0)
    {
        return true;
    }
    return false;
}
void register_customer(void)
{
    Customer A;
    fstream F;
    cout << "\n ******* Enter Information ******\n";
    cout << "\nEnter first name of your customer : ";
    cin >> A.First_name;
    cout << "\nEnter last name of your customer : ";
    cin >> A.Last_name;
    cout << "\nEnter father name of your customer : ";
    cin >> A.Father_name;
    cout << "\nEnter call number of your customer : ";
    cin >> A.call_num;
    cout << "\nCustomer enter his/her pasword : ";
    cin >> A.Pass_code;
    A.delleted = false;
    A.id = 1000 + filesize("CustomerFile.dat") / sizeof(Customer);
    F.open("CustomerFile.dat", ios::app | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again \n";
        return;
    }
    F.write((char *)&A, sizeof(Customer));
    F.close();
}
Customer register_customer(Customer A)
{

    cout << "\n ******* Enter Information ******\n";
    cout << "\nEnter first name of your customer : ";
    cin >> A.First_name;
    cout << "\nEnter last name of your customer : ";
    cin >> A.Last_name;
    cout << "\nEnter father name of your customer : ";
    cin >> A.Father_name;
    cout << "\nEnter call number of your customer : ";
    cin >> A.call_num;
    cout << "\nCustomer enter his/her pasword : ";
    cin >> A.Pass_code;
    return A;
}
void show_customer(Customer A)
{
    cout << "\n\n------------------\n\n";
    cout << "\nFirst name of your customer : " << A.First_name;
    cout << "\nLast name of your customer : " << A.Last_name;
    cout << "\nName of your customer : " << A.Father_name;
    cout << "\nCall Number of your customer : " << A.call_num;
    cout << "\nCustomer  his/her pasword : " << A.Pass_code;
    cout << "\nCustomer id : " << A.id;
    return;
}
void show_all_customer(void)
{
    ifstream F;
    Customer A;
    F.open("CustomerFile.dat", ios::in | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again\n";
        return;
    }
    F.read((char *)&A, sizeof(Customer));
    while (!F.eof())
    {
        if (!A.delleted)
        {
            show_customer(A);
        }
        F.read((char *)&A, sizeof(Customer));
    }
}
void edit_customer(void)
{
    fstream f;
    Customer A;
    int ID;
    cout << "\nEnter ID of your customer that you want to be edit ";
    cout << "\n\n>>> ";
    cin >> ID;
    int pos = ((ID)-1000) * sizeof(Customer);
    if (pos > filesize("CustomerFile.dat"))
    {
        cout << "\nWrong id enterd or we dont have any customer ";
        return;
    }
    else
    {

        f.open("CustomerFile.dat", ios::in | ios::out | ios::binary);
        if (!f.is_open())
        {
            cout << "\nWrong openning file";
            return;
        }
        else
        {
            f.seekg(pos, ios::beg);
            f.read((char *)&A, sizeof(Customer));
            show_customer(A);
            A = register_customer(A);
            f.seekg(pos, ios::beg);
            f.write((char *)&A, sizeof(Customer));
            f.close();
            return;
        }
    }
}
bool check_pas(void)
{
    char Name[31];
    char Pas[31];
    int Id;
    ifstream File;
    cout << "\ncustomer please enter your username or name : ";
    cin >> Name;
    cout << "\ncustomer please enter your pasword: ";
    cin >> Pas;
    cout << "\ncustomer please enter your id : ";
    cin >> Id;
    int pos = ((Id)-1000) * sizeof(Customer);

    if (pos > filesize("CustomerFile.dat"))
    {
        cout << "\nWrong id enterd !!! ";
        return false;
    }
    else
    {
        File.open("CustomerFile.dat", ios::in | ios::binary);
        if (!File.is_open())
        {
            cout << "\nWrong openning file";
            return false;
        }
        else
        {
            Customer A;
            File.seekg(pos, ios::beg);
            File.read((char *)&A, sizeof(Customer));
            alpha = A;
            if (strcmp(A.Pass_code, Pas) == 0 && strcmp(A.First_name, Name) == 0)
            {
                return true;
            }
            cout << "\nWrong pascode or username";
            return false;
        }
    }
}
void register_house(void)
{
    House A;
    fstream F;
    cout << "\n ******* Enter Information ******\n";
    cout << "\nEnter loc your house : ";
    cin >> A.loc;
    cout << "\nEnter masahat your house (int): ";
    cin >> A.masahat;
    cout << "\nHow many rooms that house have (int) : ";
    cin >> A.rooms;
    do
    {
        cout << "\nWhat kind is your house (enter sell/rent) : ";
        cin >> A.kind;
    } while (!(strcmp(A.kind, "sell") == 0 || strcmp(A.kind, "rent") == 0));
    cout << "\nEnter price of youer house : ";
    cin >> A.price;
    A.delleted = false;
    A.Id = 1000 + filesize("HouseFile.dat") / sizeof(House);
    F.open("HouseFile.dat", ios::app | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again \n";
        return;
    }
    F.write((char *)&A, sizeof(House));
    F.close();
    return;
}
House register_house(House A)
{
    cout << "\n ******* Enter Information ******\n";
    cout << "\nEnter loc your house : ";
    cin >> A.loc;
    cout << "\nEnter masahat your house (int): ";
    cin >> A.masahat;
    cout << "\nHow many rooms that house have (int) : ";
    cin >> A.rooms;
    do
    {
        cout << "\nWhat kind is your house (enter sell/rent) : ";
        cin >> A.kind;
    } while (!(strcmp(A.kind, "sell") == 0 || strcmp(A.kind, "rent") == 0));
    cout << "\nEnter price of youer house : ";
    cin >> A.price;
    return A;
}
void show_house(House A)
{

    cout << "\n\n------------------\n\n";
    cout << "\nHouse loc : " << A.loc;
    cout << "\nMasahar house : " << A.masahat;
    cout << "\nHow many rooms that house have (int) : " << A.rooms;
    cout << "\nHouse kind : " << A.kind;
    cout << "\nHouse price : " << A.price;
    cout << "\nHouse ID :" << A.Id;
    return;
}
void show_all_house(void)
{
    ifstream F;
    House A;
    F.open("HouseFile.dat", ios::in | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again\n";
        return;
    }
    if (filesize("HouseFile.dat") == 0)
    {
        cout << "\nNo house is register !!!! ";
        F.close();
        return;
    }

    F.read((char *)&A, sizeof(House));
    while (!F.eof())
    {
        if (!A.delleted)
        {
            show_house(A);
        }
        F.read((char *)&A, sizeof(House));
    }
    F.close();
    return;
}
void delete_house(void)
{
    fstream f;
    House A;
    if (filesize("HouseFile.dat") == 0)
    {
        cout << "\nNo house is register !!! ";
        return;
    }
    int ID;
    cout << "enter house ID to delete : ";
    cin >> ID;
    int pos = ((ID)-1000) * sizeof(House);
    if (pos > filesize("HouseFile.dat"))
    {
        cout << "\nWrong id enterd ";
        return;
    }
    else
    {

        f.open("HouseFile.dat", ios::in | ios::out | ios::binary);
        if (!f.is_open())
        {
            cout << "\nWrong openning file";
            return;
        }
        else
        {
            f.seekg(pos, ios::beg);
            f.read((char *)&A, sizeof(House));
            A.delleted = true;
            f.seekg(pos, ios::beg);
            f.write((char *)&A, sizeof(House));
            f.close();
            return;
        }
    }
}
void delete_customer(void)
{
    fstream f;
    Customer A;
    if (filesize("CustomerFile.dat") == 0)
    {
        cout << "\nNo customer is register !!! ";
        return;
    }
    int ID;
    cout << "enter house ID to delete : ";
    cin >> ID;
    int pos = ((ID)-1000) * sizeof(Customer);
    if (pos > filesize("CustomerFile.dat"))
    {
        cout << "\nWrong id enterd ";
        return;
    }
    else
    {

        f.open("CustomerFile.dat", ios::in | ios::out | ios::binary);
        if (!f.is_open())
        {
            cout << "\nWrong openning file";
            return;
        }
        else
        {
            f.seekg(pos, ios::beg);
            f.read((char *)&A, sizeof(Customer));
            A.delleted = true;
            f.seekg(pos, ios::beg);
            f.write((char *)&A, sizeof(Customer));
            f.close();
            return;
        }
    }
}
void search_house(void)
{
    ifstream F;
    House A;
    House B;
    if (filesize("HouseFile.dat") == 0)
    {
        cout << "\nNo house is register !!! ";
        return;
    }
    cout << "\nFor searching house you most complete hose kind fild and for other item if you dont caere abouth that enter 0 ";
    do
    {
        cout << "\nWhat kind is your house (enter sell/rent) : ";
        cin >> A.kind;
    } while (!(strcmp(A.kind, "sell") == 0 || strcmp(A.kind, "rent") == 0));
    cout << "\nEnter masahat your house (int): ";
    cin >> A.masahat;
    cout << "\nHow many rooms that house have (int) : ";
    cin >> A.rooms;
    cout << "\nEnter max of you bagut (int): ";
    cin >> A.price;
    F.open("HouseFile.dat", ios::in | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again\n";
        return;
    }
    else
    {
        F.read((char *)&B, sizeof(House));
        while (!F.eof())
        {
            if ((!B.delleted) && (strcasecmp(A.kind, B.kind) == 0) && (A.rooms <= B.rooms) && (B.price <= A.price) && (A.masahat <= B.masahat))
            {
                show_house(B);
            }
            F.read((char *)&B, sizeof(House));
        }
        F.close();
    }
}
void ediet_house(void)
{
    fstream f;
    House A;
    int ID;
    cout << "\nEnter ID of your house that you want to be edit ";
    cout << "\n\n>>> ";
    cin >> ID;
    int pos = ((ID)-1000) * sizeof(House);
    if (pos > filesize("HouseFile.dat"))
    {
        cout << "\nWrong id enterd or we dont have any customer ";
        return;
    }
    else
    {

        f.open("HouseFile.dat", ios::in | ios::out | ios::binary);
        if (!f.is_open())
        {
            cout << "\nWrong openning file";
            return;
        }
        else
        {
            f.seekg(pos, ios::beg);
            f.read((char *)&A, sizeof(House));
            show_house(A);
            A = register_house(A);
            f.seekg(pos, ios::beg);
            f.write((char *)&A, sizeof(House));
            f.close();
            return;
        }
    }
}
void sabt_re(void)
{
    Request D;
    int H_id;
    D.accepting = false;
    D.cancel = false;
    ifstream F;
    House Q;
    fstream G;
    D.t = alpha_t;
    if (filesize("HouseFile.dat") == 0)
    {
        cout << "\nNo house is register !!!! ";
        return;
    }
    D.A = alpha;
    cout << "\nEnter house id : ";
    cin >> H_id;
    int pos = ((H_id)-1000) * sizeof(House);
    if (pos > filesize("HouseFile.dat"))
    {
        cout << "\nWrong id enterd or we dont have any customer ";
        return;
    }
    F.open("HouseFile.dat", ios::in | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again\n";
        return;
    }
    F.seekg(pos, ios::beg);
    F.read((char *)&Q, sizeof(House));
    if (Q.delleted)
    {
        cout << "\nHouse is unavlable ";
        F.close();
        return;
    }
    D.B = Q;
    F.close();
    D.ID = 1000 + (filesize("re.dat") / sizeof(Request));
    G.open("re.dat", ios::app | ios::binary);
    if (!G.is_open())
    {
        cout << "\nWrong openning file 85";
        return;
    }
    else
    {
        G.write((char *)&D, sizeof(Request));
        G.close();
        return;
    }
}

void show_all_re(void)
{
    ifstream F;
    Request A;
    F.open("re.dat", ios::in | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again\n";
        return;
    }
    F.read((char *)&A, sizeof(Request));
    while (!F.eof())
    {
        if ((!A.cancel) && (!A.accepting))
        {
            show_re(A);
        }
        F.read((char *)&A, sizeof(Request));
    }
}
void dell_re(void)
{
    int id;
    fstream G;
    Request D;
    cout << "\nEnter your id request : ";
    cin >> id;
    int pos = ((id)-1000) * sizeof(Request);
    if (pos > filesize("re.dat"))
    {
        cout << "\nWrong id enterd or we dont have any customer ";
        return;
    }
    G.open("re.dat", ios::in | ios::out | ios::binary);
    if (!G.is_open())
    {
        cout << "\nWrong openning file";
        return;
    }
    G.seekg(pos, ios::beg);
    G.read((char *)&D, sizeof(Request));

    if (alpha.id == D.A.id)
    {
        D.cancel = true;
        G.seekg(pos, ios::beg);
        G.write((char *)&D, sizeof(Request));
        G.close();
        return;
    }
    else
    {
        cout << "\nThat is not your request id ";
        return;
    }
}
void m_report(Request A)
{
    fstream File;
    File.open("report.dat", ios::app | ios::binary);
    if (!File.is_open())
    {
        cout << "\nWrong openning file";
        return;
    }
    else
    {
        File.write((char *)&A, sizeof(Request));
        File.close();
        return;
    }
}
void accept(void)
{
    int id;
    fstream File;
    Request A;
    cout << "\nEnter id request : ";
    cin >> id;
    int pos = ((id)-1000) * sizeof(Request);
    if (pos > filesize("re.dat"))
    {
        cout << "\nWrog id !!! ";
        return;
    }
    File.open("re.dat", ios::in | ios::out | ios::binary);
    if (!File.is_open())
    {
        cout << "\nWrong openning file";
        return;
    }
    else
    {
        File.seekg(pos, ios::beg);
        File.read((char *)&A, sizeof(Request));
        if ((!A.cancel) && (!A.accepting) && (!A.B.delleted))
        {
            A.accepting = true;
            A.B.delleted = true;
            File.seekg(pos, ios::beg);
            File.write((char *)&A, sizeof(Request));
            File.close();
            m_report(A);
            return;
        }
        else
        {
            cout << "\nRequest is bee canceled or accepted ";
            File.close();
            return;
        }
    }
}
void search_customer_1(int id = alpha.id)
{
    ifstream F;
    Request A;
    F.open("report.dat", ios::in | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again\n";
        return;
    }
    F.read((char *)&A, sizeof(Request));
    while (!F.eof())
    {
        if (id == A.A.id)
        {
            show_re(A);
        }
        F.read((char *)&A, sizeof(Request));
    }
}
void search_customer(void)
{
    int id;
    Customer A;
    cout << "enter id of your customer : ";
    cin >> id;
    int pos = ((id)-1000) * sizeof(Customer);

    if (pos > filesize("CustomerFile.dat"))
    {
        cout << "\nWrong id enterd !!! ";
        return;
    }
    else
    {
        search_customer_1(id);
    }
    return;
}
void search_house_id(int id)
{
    ifstream F;
    Request A;
    F.open("report.dat", ios::in | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again\n";
        return;
    }
    F.read((char *)&A, sizeof(Request));
    while (!F.eof())
    {
        if (id == A.B.Id)
        {
            show_re(A);
        }
        F.read((char *)&A, sizeof(Request));
    }
    F.close();
    return;
}
void search_house_id(void)
{
    int id;
    Customer A;
    cout << "enter id of your house : ";
    cin >> id;
    int pos = ((id)-1000) * sizeof(Customer);

    if (pos > filesize("HouseFile.dat"))
    {
        cout << "\nWrong id enterd !!! ";
        return;
    }
    else
    {
        search_house_id(id);
    }
    return;
}
void menue_srearch(void)
{
    int chose;
    do
    {
        cout << "\nFor get report for customer enter 1 ";
        cout << "\nFor get report for house enter 2 ";
        cout << "\nFor go back enter 0";
        cout << "\n>>> ";
        cin >> chose;
        switch (chose)
        {
        case 1:
            search_customer();
            break;
        case 2:
            search_house_id();
            break;
        case 0:
            return;
            break;
        default:
            break;
        }
    } while (chose != 0);
}
void menue_customer(void)
{
    cout << "\n\n\nwork whit custome edit/add/dellet \n\n\n";
    int chose;
    do
    {
        cout << "\n\n";
        cout << "\nFor add customer enter 1";
        cout << "\nFor edit customer profile enter 2";
        cout << "\nFor dellet customer enter 3";
        cout << "\nFor see list of all customers enter 4";
        cout << "\nFor exit that menue enter 0";
        cout << "\n\n>>> ";
        cin >> chose;
        switch (chose)
        {
        case 1:
            register_customer();
            break;
        case 2:
            edit_customer();
            break;
        case 3:
            delete_customer();
            break;
        case 4:
            show_all_customer();
            break;
        case 0:
            return;
            break;

        default:
            break;
        }
    } while (chose != 0);
    return;
}
void menue_for_customer(void)
{
    cout << "\n\n";
    int chose;
    do
    {
        cout << "\nFor search house enter 1";
        cout << "\nFor pishnahad enter 2";
        cout << "\nFor dellet pishnahad enter 3";
        cout << "\nFor View past purchases enter 4";
        cout << "\nFor exit that menue enter 0";
        cout << "\n\n>>> ";
        cin >> chose;
        switch (chose)
        {
        case 1:
            search_house();
            break;
        case 2:
            sabt_re();
            break;
        case 3:
            dell_re();
            break;
        case 4:
            search_customer_1();
            break;
        case 0:
            return;
            break;

        default:
            break;
        }
    } while (chose != 0);
    return;
}
void menue_house(void)
{
    cout << "\n\n";
    cout << "\n\n\nwork whit house edit/add/dellet/search \n\n\n";
    int chose;
    do
    {
        cout << "\nFor add house enter 1";
        cout << "\nFor edit house profile enter 2";
        cout << "\nFor dellet house enter 3";
        cout << "\nFor search house enter 4";
        cout << "\nFor exit that menue enter 0";
        cout << "\n\n>>> ";
        cin >> chose;
        switch (chose)
        {
        case 1:
            register_house();
            break;
        case 2:
            ediet_house();
            break;
        case 3:
            delete_house();
            break;
        case 4:
            search_house();
            break;
        case 0:
            return;
            break;

        default:
            break;
        }
    } while (chose != 0);
    return;
}
void menue_for_admin(Admin name)
{
    int chose;
    do
    {
        cout << "\n\n\nHello " << name.username << "\n\n\n";
        cout << "\nFor see list of house enter 1 ";
        cout << "\nFor add house enter 2 ";
        cout << "\nFor edit/add/delet/search house enter 3 ";
        cout << "\nFor edit/add/delet customer enter 4";
        cout << "\nFor Contracting enter 5";
        cout << "\nFor see history of customers and house enter 6 ";
        cout << "\nFor see history house within a specified timeframe enter 7 ";
        cout << "\nFor go to the main menue enter 0";
        cout << "\n\n>>> ";
        cin >> chose;
        switch (chose)
        {
        case 1:
            show_all_house();
            break;
        case 2:
            register_house();
            break;
        case 3:
            menue_house();
            break;
        case 4:
            menue_customer();
            break;
        case 5:
            show_all_re();
            accept();
            break;
        case 6:
            menue_srearch();
            break;
        case 7:
            time_search();
            break;
        case 0:
            return;
            break;

        default:
            break;
        }
    } while (chose != 0);
    return;
}
int main(void)
{
    alpha_t.get_tiem();
    Admin arian;
    arian.set("Arian", "1401");
    int type;
    bool flag;
    do
    {
        cout << "\nif your admin enter 1 ";
        cout << "\nif your customer enter 2 ";
        cout << "\nif you want to close app enter 0 : ";
        cout << "\n\n>>> ";
        cin >> type;
        switch (type)
        {
        case 1:
            flag = check_pas(arian);
            while (!flag)
            {
                cout << "\n wrong user name or pasword please try again \n";
                flag = check_pas(arian);
            }
            menue_for_admin(arian);
            break;
        case 2:

            flag = check_pas();
            while (!flag)
            {
                cout << "\n wrong user name or pasword please try again \n";
                flag = check_pas();
            }
            menue_for_customer();
            break;
        default:
            break;
        }
    } while (0 != type);
    return 0;
}