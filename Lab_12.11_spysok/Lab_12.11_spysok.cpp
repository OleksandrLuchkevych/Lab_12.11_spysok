#include <iostream>
#include <string>

using namespace std;

struct Flat {
    int rooms;
    int floor;
    double area;
    string address;
    Flat* next;
};

void addFlat(Flat*& head, const Flat& flat) {
    Flat* newNode = new Flat;
    newNode->rooms = flat.rooms;
    newNode->floor = flat.floor;
    newNode->area = flat.area;
    newNode->address = flat.address;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    }
    else {
        Flat* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void removeFlat(Flat*& head, const Flat& flat) {
    if (head == nullptr) {
        return;
    }

    if (head->rooms == flat.rooms && head->floor == flat.floor && (head->area - flat.area) <= (0.1 * head->area)) {
        Flat* temp = head;
        head = head->next;
        delete temp;
    }
    else {
        Flat* prev = head;
        Flat* curr = head->next;
        while (curr != nullptr) {
            if (curr->rooms == flat.rooms && curr->floor == flat.floor && (curr->area - flat.area) <= (0.1 * curr->area)) {
                prev->next = curr->next;
                delete curr;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }
}

void printAllFlats(const Flat* head) {
    const Flat* temp = head;
    while (temp != nullptr) {
        cout << "Rooms: " << temp->rooms << ", Floor: " << temp->floor << ", Area: " << temp->area << ", Address: " << temp->address << endl;
        temp = temp->next;
    }
}

Flat enterFlatInfo() {
    Flat flat;
    cout << "Enter the number of rooms: ";
    cin >> flat.rooms;
    cout << "Enter the floor: ";
    cin >> flat.floor;
    cout << "Enter the area: ";
    cin >> flat.area;
    cout << "Enter the address: ";
    cin.ignore();
    getline(cin, flat.address);
    return flat;
}

void printFlat(const Flat& flat) {
    cout << "Rooms: " << flat.rooms << ", Floor: " << flat.floor << ", Area: " << flat.area << ", Address: " << flat.address << endl;
}

int main() {
    Flat* head = nullptr;  // Початковий вузол списку

    // Початкове формування картотеки
    Flat flat1{ 2, 3, 80.5, "Address 1", nullptr };
    Flat flat2{ 3, 5, 120.0, "Address 2", nullptr };
    Flat flat3{ 1, 2, 50.0, "Address 3", nullptr };

    addFlat(head, flat1);
    addFlat(head, flat2);
    addFlat(head, flat3);

    // Введення заявки на обмін
    Flat requestedFlat = enterFlatInfo();

    

    // Пошук відповідного варіанту і вилучення з картотеки
    removeFlat(head, requestedFlat);

    // Виведення квартири, яку ввели з клавіатури
    cout << "Requested Flat: ";
    printFlat(requestedFlat);

    // Додавання заявки до картотеки
    addFlat(head, requestedFlat);

    // Виведення всього списку
    printAllFlats(head);

 

    // Звільнення пам'яті
    Flat* temp = head;
    while (temp != nullptr) {
        Flat* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    return 0;
}
