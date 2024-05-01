#include <iostream>
using namespace std;

#define NBUCKET 10  // Number of buckets
#define INTERVAL 10  // Each bucket capacity

struct Node {
    int data; //· Œ“Ì‰ «·ﬁÌ„…
    struct Node* next; //· Œ“Ì‰ ⁄‰Ê«‰ «·⁄‰’— «· «·Ì ›Ì «·ﬁ«∆„… 
};

void BucketSort(int arr[], int size);//·«” ﬁ»«· „’›Ê›… „‰ «·«⁄œ«œ «·’ÕÌÕ… 
struct Node* InsertionSort(struct Node* list);
void print(int arr[], int size);
void printBuckets(struct Node* list);
int getBucketIndex(int value);

// Sorting function
void BucketSort(int arr[], int size) {
    int i;
    struct Node** buckets;

    // Find the maximum element in the array
    int max = arr[0];
    for (i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Determine the number of buckets based on the maximum element
    int num_buckets = (max / INTERVAL) + 1;

    // Create buckets and allocate memory size
    buckets = (struct Node**)malloc(sizeof(struct Node*) * num_buckets);

    // Initialize empty buckets
    for (i = 0; i < num_buckets; ++i) {
        buckets[i] = NULL;
    }

    // Fill the buckets with respective elements
    for (i = 0; i < size; ++i) {
        struct Node* current;
        int pos = getBucketIndex(arr[i]);
        current = (struct Node*)malloc(sizeof(struct Node));
        current->data = arr[i];
        current->next = buckets[pos];
        buckets[pos] = current;
    }

    // Print the buckets along with their elements
    for (i = 0; i < num_buckets; i++) {
        cout << "Bucket[" << i << "] : ";
        printBuckets(buckets[i]);
        cout << endl;
    }

    // Sort the elements of each bucket
    for (i = 0; i < num_buckets; ++i) {
        buckets[i] = InsertionSort(buckets[i]);
    }

    cout << "-------------" << endl;
    cout << "Buckets after sorted" << endl;
    for (i = 0; i < num_buckets; i++) {
        cout << "Bucket[" << i << "] : ";
        printBuckets(buckets[i]);
        cout << endl;
    }

    // Put sorted elements on arr
    int j = 0;
    for (i = 0; i < num_buckets; ++i) {
        struct Node* node;
        node = buckets[i];
        while (node) {
            arr[j++] = node->data;
            node = node->next;
        }
    }

    // Free allocated memory
    for (i = 0; i < num_buckets; ++i) {
        struct Node* node;
        node = buckets[i];
        while (node) {
            struct Node* tmp;
            tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(buckets);
    return;
}

// Function to sort the elements of each bucket
struct Node* InsertionSort(struct Node* list) {
    struct Node* k, * nodeList;
    if (list == 0 || list->next == 0) {
        return list;
    }

    nodeList = list;
    k = list->next;
    nodeList->next = 0;
    while (k != 0) {
        struct Node* ptr;
        if (nodeList->data > k->data) {
            struct Node* tmp;
            tmp = k;
            k = k->next;
            tmp->next = nodeList;
            nodeList = tmp;
            continue;
        }

        for (ptr = nodeList; ptr->next != 0; ptr = ptr->next) {
            if (ptr->next->data > k->data)
                break;
        }

        if (ptr->next != 0) {
            struct Node* tmp;
            tmp = k;
            k = k->next;
            tmp->next = ptr->next;
            ptr->next = tmp;
            continue;
        }
        else {
            ptr->next = k;
            k = k->next;
            ptr->next->next = 0;
            continue;
        }
    }
    return nodeList;
}

int getBucketIndex(int value) {
    return value / INTERVAL;
}

// Print buckets
void print(int ar[], int size) {
    int i;
    for (i = 0; i < size; ++i) {
        cout << ar[i] << " ";
    }
    cout << endl;
}

void printBuckets(struct Node* list) {
    struct Node* cur = list;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
}

// Driver code
int main(void) {
    int size;
    cout << "Enter the number of elements: ";
    cin >> size;

    int* array = new int[size];

    cout << "Enter the elements of the array:" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }

    cout << "Initial array: " << endl;
    print(array, size);
    cout << "-------------" << endl;

    BucketSort(array, size);
    cout << "-------------" << endl;
    cout << "Sorted array: " << endl;
    print(array, size);

    delete[] array;
    return 0;
}
