#include <iostream>

using namespace std;

// Cấu trúc cho 1 node
struct Node
{
    int data;
    Node *pNext;
};

// Cấu trúc cho danh sách liên kết đơn
struct List
{
    Node *pHead;
    Node *pTail;
};

// Khởi tạo danh sách liên kết rỗng
void createEmptyList(List &l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}

// Tạo 1 phần tử mới
Node *createNode(int x)
{
    Node *p;
    p = new Node;
    if (p == NULL)
        exit(1);
    p->data = x;
    p->pNext = NULL;
    return p;
}

// // Thêm phần tử vào đầu danh sách (dạng int)
// void addHead(List &l, int x)
// {
//     Node *p = createNode(x);
//     if (l.pHead == NULL)
//     {
//         l.pHead = p;
//         l.pTail = l.pHead;
//     }
//     else
//     {
//         p->pNext = l.pHead;
//         l.pHead = p;
//     }
// }

// Thêm Node vào đầu danh sách
void addHead(List &l, Node *p)
{
    if (l.pHead == NULL)
    {
        l.pHead = p;
        l.pTail = l.pHead;
    }
    else
    {
        p->pNext = l.pHead;
        l.pHead = p;
    }
}

// Thêm phần tử vào cuối danh sách
void addTail(List &l, Node *p)
{
    // Node *p = createNode(x);
    if (l.pHead == NULL)
    {
        l.pHead = p;
        l.pTail = l.pHead;
    }
    else
    {
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

// Thêm Node p vào sau Node Q
void addAfterQ(List &l, Node *p, Node *Q)
{
    if (Q != NULL)
    {
        p->pNext = Q->pNext;
        Q->pNext = p;
        if (Q == l.pTail)
            l.pTail = p;
    }
    else
        addHead(l, p);
}

// In ra danh sách
void printList(List l)
{
    Node *p;
    if (l.pHead == NULL)
        cout << "DSLK rong.\n";
    else
    {
        p = l.pHead;
        cout << "Danh sach lien ket la: \n";
        while (p)
        {
            cout << p->data << "\t";
            p = p->pNext;
        }
        cout << "\n";
    }
    cout << "-------------------------\n";
}

// Hủy phần tử đầu trong danh sách
bool deleteHead(List &l)
{
    Node *p;
    if (l.pHead != NULL)
    {
        p = l.pHead;
        l.pHead = l.pHead->pNext;
        if (l.pHead == NULL)
            l.pTail = NULL;
        delete p;
        return 1;
    }
    return 0;
}

// Hủy Node sau Node Q
bool deleteAfterQ(List &l, Node *Q)
{
    Node *p;
    if (Q != NULL)
    {
        p = Q->pNext;
        if (p != NULL)
        {
            Q->pNext = p->pNext;
            if (p == l.pTail)
                l.pTail = Q;
            delete p;
            return 1;
        }
    }
    return 0;
}

// Xóa phần tử có khóa x
bool deleteX(List &l, int x)
{
    Node *p, *Q;
    Q = NULL;
    p = l.pHead;
    while (p != NULL && p->data != x)
    {
        Q = p;
        p = p->pNext;
    }
    if (p == NULL)
        return 0;
    if (Q != NULL)
        deleteAfterQ(l, Q);
    else
        deleteHead(l);
    return 1;
}

// Tìm Node trong danh sách
Node *searchNode(List l, int x)
{
    Node *p;
    p = l.pHead;
    while (p != NULL && p->data != x)
        p = p->pNext;
    return p;
}

// Hủy danh sách
void removeList(List &l)
{
    Node *p;
    while (l.pHead != NULL)
    {
        p = l.pHead;
        l.pHead = l.pHead->pNext;
        delete p;
    }
    l.pTail = NULL;
}

// lấy phần tử pivot
Node *separateHead(List &l)
{
    Node *p = l.pHead;
    if (p == NULL)
        return NULL;
    l.pHead = l.pHead->pNext;
    if (l.pHead == NULL)
        l.pTail = NULL;
    p->pNext = NULL;
    return p;
}

// Chia dãy con cho quick sort
void partition(List &l, List &l1, Node *&pivot, List &l2)
{
    Node *p;
    if (l.pHead == NULL)
        return;
    pivot = separateHead(l);
    while (l.pHead != NULL)
    {
        p = separateHead(l);
        if (p->data <= pivot->data)
            addTail(l1, p);
        else
            addTail(l2, p);
    }
}

// Trộn dãy con cho quick sort
void join(List &l, List &l1, Node *&pivot, List &l2)
{
    Node *p;
    while (l1.pHead != NULL)
    {
        p = separateHead(l1);
        addTail(l, p);
    }
    addTail(l, pivot);
    while (l2.pHead != NULL)
    {
        p = separateHead(l2);
        addTail(l, p);
    }
}

// Sắp xếp danh sách
void quickSort(List &l)
{
    List l1, l2;
    createEmptyList(l1);
    createEmptyList(l2);
    Node *pivot;
    partition(l, l1, pivot, l2);
    if (l1.pHead != l1.pTail)
        quickSort(l1);
    if (l2.pHead != l2.pTail)
        quickSort(l2);
    join(l, l1, pivot, l2);
}

// Xuất thông báo
void notification(char &ch)
{
    cout << " 1 : Them phan tu vao dau danh sach\n";
    cout << " 2 : Them phan tu vao sau phan tu Q danh sach\n";
    cout << " 3 : Them phan tu vao cuoi danh sach\n";
    cout << " 4 : Xoa phan tu o dau danh sach\n";
    cout << " 5 : Xoa phan tu o sau phan tu Q\n";
    cout << " 6 : Xoa phan tu co khoa x\n";
    cout << " 7 : Tim phan tu x trong danh sach\n";
    cout << " 8 : Sap xep danh sach \n";
    cout << " 9 : In ra danh sach\n";
    cout << " 0 : Thoat!!";
    cout << "\n-------------------------\n";
    cin >> ch;
    cout << "-------------------------\n";
}

// Xử lý case 1
void handle1(List &l)
{
    int x;
    cout << "Nhap vao gia tri: ";
    cin >> x;
    addHead(l, createNode(x));
    cout << "Da them phan tu " << x << " vao dau danh sach";
    cout << "\n-------------------------\n";
}

// Xử lý case 2
void handle2(List &l)
{
    int x;
    Node *Q;
    cout << "Nhap vao gia tri cua phan tu Q: ";
    cin >> x;
    Q = searchNode(l, x);
    cout << "Nhap vao gia tri muon them: ";
    cin >> x;
    addAfterQ(l, createNode(x), Q);
    if (Q == NULL)
        cout << "Khong co phan tu Q trong danh sach. Phan tu " << x << " duoc them vao dau danh sach\n";
    else
        cout << "Da them phan tu " << x << " vao sau phan tu Q\n";
    cout << "-------------------------\n";
}

// Xử lý case 3
void handle3(List &l)
{
    int x;
    cout << "Nhap vao gia tri: ";
    cin >> x;
    addTail(l, createNode(x));
    cout << "Da them phan tu " << x << " vao cuoi danh sach";
    cout << "\n-------------------------\n";
}

// Xử lý case 5
void handle5(List &l)
{
    int x;
    Node *Q;
    cout << "Nhap vao gia tri cua phan tu Q: ";
    cin >> x;
    Q = searchNode(l, x);
    if (deleteAfterQ(l, Q))
        cout << "Da xoa phan tu sau phan tu Q";
    else
        cout << "Khong co phan tu Q trong danh sach. Khong thuc hien lenh xoa";
    cout << "\n-------------------------\n";
}

// Xử lý case 6
void handle6(List &l)
{
    int x;
    cout << "Nhap vao gia tri cua phan tu can xoa: ";
    cin >> x;
    if (deleteX(l, x))
        cout << "Da xoa phan tu co khoa bang " << x << " trong danh sach";
    else
        cout << "Khong co phan tu co khoa bang " << x << " trong danh sach. Khong thuc hien lenh xoa";
    cout << "\n-------------------------\n";
}

// Xử lý case 7
void handle7(List &l)
{
    int x;
    Node *p;
    cout << "Nhap vao gia tri phan tu can tim: ";
    cin >> x;
    p = searchNode(l, x);
    if (p == NULL)
        cout << "Khong co phan tu co gia tri " << x << " trong danh sach";
    else
        cout << "Dia chi cua phan tu can tim la: " << p;
    cout << "\n-------------------------\n";
}

void handle(List &l)
{
    char ch;
    Node *Q;
    do
    {
        notification(ch);
        switch (ch)
        {
        case '1':
            handle1(l);
            break;
        case '2':
            handle2(l);
            break;
        case '3':
            handle3(l);
            break;
        case '4':
        {
            deleteHead(l);
            cout << "Da xoa phan tu dau danh sach";
            cout << "\n-------------------------\n";
            break;
        }
        case '5':
            handle5(l);
            break;
        case '6':
            handle6(l);
            break;
        case '7':
            handle7(l);
            break;
        case '8':
        {
            quickSort(l);
            cout << "Da sap xep danh sach theo thu tu tang dan";
            cout << "\n-------------------------\n";
            break;
        }
        case '9':
            printList(l);
            break;
        default:
        {
            ch = '0';
            cout << "Dang thoat chuong trinh .... ";
            cout << "\n-------------------------\n";
        }
        }
    } while (ch != '0');
}

int main()
{
    List l;
    createEmptyList(l);
    handle(l);
    return 0;
}