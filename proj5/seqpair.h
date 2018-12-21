typedef struct Node {
int label;
double height;
double width;
double xcoor;
double ycoor;
struct Node *next;
} Node;


Node *Load_Into_Tree(char* Filename);

void save_coordinates(Node* tree, FILE* fp);

