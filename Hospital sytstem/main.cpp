#include <iostream>
using namespace std;

const int MAX_SPECIALIZATION = 20;
const int MAX_QUEUE = 5;

string names[MAX_SPECIALIZATION+1][MAX_QUEUE+1];
int status[MAX_SPECIALIZATION+1][MAX_QUEUE+1];          // 0 for regular , 1 for urgent
int queue_length[MAX_SPECIALIZATION+1];                 // how many patients for each specialization

int menu() {
    int choice = -1;
    while (choice == -1) {
        cout << "\nEnter your choice:\n";
        cout << "1) Add new patient\n";
        cout << "2) Print all patients\n";
        cout << "3) Get next patient\n";
        cout << "4) Exit\n";

        cin >> choice;

        if (!(1 <= choice && choice <= 4)) {
            cout << "Invalid choice. Try again\n";
            choice = -1;
        }
    }
    return choice;
}

// Help in adding patient
void right_shifting(int spec, string names_sp[], int status_sp[]){
    int length = queue_length[spec];
    for (int i = length-1; i >= 0  ; --i) {
        names_sp[i+1] = names_sp[i];
        status_sp[i+1] = status_sp[i];
    }
    queue_length[spec]++;
}

// Help in removing patient
void left_shifting(int spec, string names_sp[], int status_sp[]){
    int length = queue_length[spec];
    for (int i = 1; i < length; ++i) {
        names_sp[i-1] = names_sp[i];
        status_sp[i-1] = status_sp[i];
    }
    queue_length[spec]--;
}

bool add_patient(){
    int stat ;
    int spec;
    string  name;

    cout << "Enter specialization, name, status: ";
    cin >> spec >> name >> stat;


    int position = queue_length[spec];
    if (position >= MAX_QUEUE) {
        cout << "Sorry we can't add more patients for this specialization\n";
        return false;
    }
    if(stat == 0){          // regular, add to end
        names[spec][position] = name;
        status[spec][position] = stat;
        queue_length[spec]++;
    }
    else{
        // urgent, add to begin. Shift, then add
        right_shifting(spec,names[spec],status[spec]);
        names[spec][0] = name;
        status[spec][0] = stat;
    }
    return true;
}
void print_patient(int spec, string names_sp[], int status_sp[]) {
    int len = queue_length[spec];
    if (len == 0)
        return;

    cout << "There are " << len << " patients in specialization " << spec << "\n";
    for (int i = 0; i < len; ++i) {
        cout << names_sp[i] << " ";
        if (status_sp[i])
            cout << "urgent\n";
        else
            cout << "regular\n";
    }
    cout << "\n";
}

void print_patients() {
    cout << "****************************\n";
    for (int spec = 0; spec < MAX_SPECIALIZATION; ++spec) {
        print_patient(spec, names[spec], status[spec]);
    }
}

void get_next_patients() {
    int spec;
    cout << "Enter specialization: ";
    cin >> spec;

    int len = queue_length[spec];

    if(len == 0) {
        cout<<"No patients at the moment. Have rest, Dr\n";
        return;
    }

    // Let patient goes to dr
    cout<<names[spec][0]<<" please go with the Dr\n";

    // delete the patient in position 0
    left_shifting(spec, names[spec], status[spec]);
}

void hospital_system(){
    while(true){
        int choice = menu();

        if(choice == 1)
            add_patient();
        else if (choice == 2)
            print_patients();
        else if (choice == 3)
            get_next_patients();
        else
            break;
    }
}
int main() {
    hospital_system();
    return 0;
}

