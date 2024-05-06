#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Person;
struct Node;
struct List;
struct FamilyTree;

void initList(List* list);
void initFamilyTree(FamilyTree* familyTree);

Person* createPerson();

void addPersonToFamilyTree(FamilyTree* familyTree, Person* person);
void addPersonToList(List* list, Person* person);
void addChildren(Person* parent, Person* child);

Person* findPerson(const FamilyTree* familyTree, const string& name);

void printPersonInfo(const Person* person);
void printPersonWithChildren(const Person* person);
void printFamily(const Person* person, int generation);

void deleteList(List* list);
void deletePerson(Person* person);
void deleteFamilyTree(FamilyTree* familyTree);

typedef struct Node {
    Person* person;
    Node* next;
} Node;

typedef struct List {
    Node* first;
    Node* last;
} List;

typedef struct Person {
    string name;
    string birth;
    Person* father;
    List children;
    Person* next;
} Person;

typedef struct FamilyTree {
    Person* first;
    Person* last;
} FamilyTree;

int main() {
    FamilyTree familyTree;
    initFamilyTree(&familyTree);

    int choice;
    string name;

    do {
        cout << "1. Them thanh vien moi vao pha he" << endl;
        cout << "2. Them con vao 1 thanh vien da co trong pha he" << endl;
        cout << "3. Tim va hien thi thong tin cua cha va con trong pha he" << endl;
        cout << "4. Hien thi toan bo pha he" << endl;
        cout << "5. Thoat" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cin.ignore(); // Clear the input buffer
                Person* newPerson = createPerson();
                addPersonToFamilyTree(&familyTree, newPerson);
                cout << "Them thanh cong!" << endl;
                break;
            }
            case 2: {
                cin.ignore(); // Clear the input buffer
                cout << "Nhap ten cha: ";
                getline(cin, name);
                Person* parent = findPerson(&familyTree, name);
                if (parent == NULL) {
                    cout << "Khong tim thay nguoi cha trong pha he!" << endl;
                } else {
                    Person* newChild = createPerson();
                    addPersonToFamilyTree(&familyTree, newChild);
                    addChildren(parent, newChild);
                    cout << "Them thanh cong!" << endl;
                }
                break;
            }
            case 3: {
                cin.ignore(); // Clear the input buffer
                cout << "Nhap then thanh vien can tim: ";
                getline(cin, name);
                Person* foundPerson = findPerson(&familyTree, name);
                if (foundPerson != NULL) {
                    printPersonWithChildren(foundPerson);
                } else {
                    cout << "Khong tim thay thanh vien trong pha he!" << endl;
                }
                break;
            }
            case 4: {
                printFamily(familyTree.first, 0);
                break;
            }
            case 5: {
                cout << "Thoat chuong trinh!" << endl;
                break;
            }
            default:
                cout << "Lua chon khong hop le, vui long chon lai!" << endl;
        }

        cout << endl;
        system("pause");
        system("cls");
    } while (choice != 5);

    deleteFamilyTree(&familyTree);

    return 0;
}

void initList(List* list) {
    list->first = NULL;
    list->last = NULL;
}

void initFamilyTree(FamilyTree* familyTree) {
    familyTree->first = NULL;
    familyTree->last = NULL;
}

Person* createPerson() {
    string name, birth;
    cout << "Nhap ten: ";
    getline(cin, name);
    cout << "Nhap ngay sinh: ";
    cin >> birth;
    Person* p = new Person;
    p->name = name;
    p->birth = birth;
    p->father = NULL;
    initList(&(p->children));
    p->next = NULL;
    return p;
}

void addPersonToFamilyTree(FamilyTree* familyTree, Person* person) {
    if (familyTree->first == NULL) {
        familyTree->first = person;
        familyTree->last = person;
    } else {
        familyTree->last->next = person;
        familyTree->last = person;
    }
}

void addPersonToList(List* list, Person* person) {
    Node* node = new Node;
    node->person = person;
    node->next = NULL;

    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        list->last = node;
    }
}

void addChildren(Person* parent, Person* child) {
    child->father = parent;
    addPersonToList(&(parent->children), child);
}

Person* findPerson(const FamilyTree* familyTree, const string& name) {
    Person* person = familyTree->first;
    while (person != NULL) {
        if (person->name == name) {
            return person;
        }
        person = person->next;
    }
    return NULL;
}

void printPersonInfo(const Person* person) {
    if (person != NULL) {
        cout << "Name: " << person->name << "\t";
        cout << "Birth: " << person->birth << endl;
    } 
}

void printPersonWithChildren(const Person* person) {
    printPersonInfo(person);

    if (person->children.first != NULL) {
        cout << "Children: ";
        Node* node = person->children.first;
        while (node != NULL) {
            cout << node->person->name << " ";
            node = node->next;
        }
        cout << endl;
    }
    cout << endl;
}

void printFamily(const Person* person, int generation = 0) {

    if (person == NULL) {
        return;
    }

    for (int i = 0; i < generation; ++i) {
        cout << "  ";  // Indentation for readability
    }

    printPersonInfo(person);

    Node* node = person->children.first;
    while (node != NULL) {
        printFamily(node->person, generation + 1);  // Recursive call for each child
        node = node->next;
    }
}

void deleteList(List* list) {
    Node* node = list->first;
    while (node != NULL) {
        Node* temp = node;
        node = node->next;
        deletePerson(temp->person);
        delete temp;
    }
    list->first = NULL;
    list->last = NULL;
}

void deletePerson(Person* person) {
    deleteList(&(person->children));
    delete person;
}

void deleteFamilyTree(FamilyTree* familyTree) {
    Person* person = familyTree->first;
    while (person != NULL) {
        Person* temp = person;
        person = person->next;
        deletePerson(temp);
    }
    familyTree->first = NULL;
    familyTree->last = NULL;
}