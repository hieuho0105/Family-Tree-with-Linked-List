#include <iostream>
#include <string>

struct Person;
struct DNode;
struct DList;
struct FamilyTree;

void initDList(DList* list);
void initFamilyTree(FamilyTree* familyTree);
Person* createPerson(const std::string& name, const std::string& birth);
void addPersonToFamilyTree(FamilyTree* familyTree, Person* person);
void addPersonToDList(DList* list, Person* person);
void addCon(Person* parent, Person* child);
Person* findPerson(FamilyTree* familyTree, const std::string& name);
void printPersonInfo(const Person* person);
void printPersonWithChildren(const Person* person);
void deleteDList(DList* list);
void deletePerson(Person* person);
void deleteFamilyTree(FamilyTree* familyTree);

typedef struct DNode {
    Person* person;
    DNode* next;
} DNode;

typedef struct DList {
    DNode* first;
    DNode* last;
} DList;

typedef struct Person {
    std::string name;
    std::string birth;
    Person* father;
    DList children;
    Person* next;
} Person;

typedef struct FamilyTree {
    Person* first;
    Person* last;
} FamilyTree;

void initDList(DList* list) {
    list->first = nullptr;
    list->last = nullptr;
}

void initFamilyTree(FamilyTree* familyTree) {
    familyTree->first = nullptr;
    familyTree->last = nullptr;
}

Person* createPerson(const std::string& name, const std::string& birth) {
    Person* p = new Person;
    p->name = name;
    p->birth = birth;
    p->father = nullptr;
    initDList(&(p->children));
    p->next = nullptr;
    return p;
}

void addPersonToFamilyTree(FamilyTree* familyTree, Person* person) {
    if (familyTree->first == nullptr) {
        familyTree->first = person;
        familyTree->last = person;
    } else {
        familyTree->last->next = person;
        familyTree->last = person;
    }
}

void addPersonToDList(DList* list, Person* person) {
    DNode* node = new DNode;
    node->person = person;
    node->next = nullptr;

    if (list->first == nullptr) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        list->last = node;
    }
}

void addCon(Person* parent, Person* child) {
    child->father = parent;
    addPersonToDList(&(parent->children), child);
}

Person* findPerson(FamilyTree* familyTree, const std::string& name) {
    Person* person = familyTree->first;
    while (person != nullptr) {
        if (person->name == name) {
            return person;
        }
        person = person->next;
    }
    return nullptr;
}

void printPersonInfo(const Person* person) {
    std::cout << "Name: " << person->name << "\t";
    std::cout << "Birth: " << person->birth << std::endl;
}

void printPersonWithChildren(const Person* person) {
    printPersonInfo(person);

    if (person->children.first != nullptr) {
        std::cout << "Children: ";
        DNode* node = person->children.first;
        while (node != nullptr) {
            std::cout << node->person->name << " ";
            node = node->next;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printFamily(const Person* person, int generation = 0) {
    for (int i = 0; i < generation; ++i) {
        std::cout << "  ";  // Indentation for readability
    }

    printPersonInfo(person);

    DNode* node = person->children.first;
    while (node != nullptr) {
        printFamily(node->person, generation + 1);  // Recursive call for each child
        node = node->next;
    }
}

void deleteDList(DList* list) {
    DNode* node = list->first;
    while (node != nullptr) {
        DNode* temp = node;
        node = node->next;
        deletePerson(temp->person);
        delete temp;
    }
    list->first = nullptr;
    list->last = nullptr;
}

void deletePerson(Person* person) {
    deleteDList(&(person->children));
    delete person;
}

void deleteFamilyTree(FamilyTree* familyTree) {
    Person* person = familyTree->first;
    while (person != nullptr) {
        Person* temp = person;
        person = person->next;
        deletePerson(temp);
    }
    familyTree->first = nullptr;
    familyTree->last = nullptr;
}

int main() {
    FamilyTree familyTree;
    initFamilyTree(&familyTree);

    Person* p1 = createPerson("A", "1/1/2000");
    addPersonToFamilyTree(&familyTree, p1);

    Person* p2 = createPerson("B", "2/2/2000");
    addCon(p1, p2);

    Person* p3 = createPerson("C", "3/3/2000");
    addCon(p1, p3);

    Person* p4 = createPerson("D", "4/4/2000");
    addCon(p1, p4);

    Person* p5 = createPerson("E", "5/5/2000");
    addCon(p1, p5);

    Person* p6 = createPerson("F", "6/6/2000");
    addCon(p2, p6);

    Person* p7 = createPerson("G", "7/7/2000");
    addCon(p2, p7);

    Person* foundPerson = findPerson(&familyTree, "A");
    if (foundPerson != nullptr) {
        printPersonWithChildren(foundPerson);
    }

    printFamily(p1);

    deleteFamilyTree(&familyTree);

    return 0;
}