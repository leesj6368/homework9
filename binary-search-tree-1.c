#include <stdio.h>
#include <stdlib.h>

typedef struct node {//노드에 구조체 선언
	int key; 
	struct node *left; //왼쪽노드와 오른쪽 노드를 포인터 형태로 선언
	struct node *right;
} Node;

int initializeBST(Node** h);//이진 탐색 트리를 초기화하는 함수
void inorderTraversal(Node* ptr);//중위순회
void preorderTraversal(Node* ptr);//전위순회
void postorderTraversal(Node* ptr);//후위순회
int insert(Node* head, int key); //트리에 노드 삽입
int deleteLeafNode(Node* head, int key); //단말 노드 삭제
Node* searchRecursive(Node* ptr, int key);//노드탐색 
Node* searchIterative(Node* head, int key);//노드탐색  
int freeBST(Node* head); //이진 탐색 트리에 대해 동적 메모리 할당 해제

int main()
{
	char command;
	int key;
	Node* head = NULL;//head와 ptr 초기화
	Node* ptr = NULL;

	printf("[----- [leeseonjue] [2021041042] -----]");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);//이진 탐색 트리 초기화
			break;
		case 'q': case 'Q':
			freeBST(head);//동적 메모리 해제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);//key 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);//단말 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);//트리 탐색하고 그 값을 ptr에 대입
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);//검색 재귀
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);//중위순회
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);//전위순회
			break;
		case 't': case 'T':
			postorderTraversal(head->left);//후위순회

			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {//이진 탐색 트리 초기화

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);//메모리 해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));//Node를 동적 메모리 할당 해제
	(*h)->left = NULL;//왼쪽 노드 초기화
	(*h)->right = *h;//오른쪽 노드에 할당한 메모리 대입
	(*h)->key = -9999;//key 값 초기화
	return 1;
}



void inorderTraversal(Node* ptr)//중위순회
{
	if(ptr) {
		inorderTraversal(ptr->left);//ptr 노드의 왼쪽, 오른쪽 모두 중회순회함수 호출을 통해 값 넣기
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)//전위순회
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);//ptr 노드의 왼쪽, 오른쪽 모두 전회순회함수 호출을 통해 값 넣기
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)//후위순회
{
	if(ptr) {
		postorderTraversal(ptr->left);//ptr 노드의 왼쪽, 오른쪽 모두 후위순회함수 호출을 통해 값 넣기
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)//헤드노드에 값 삽입
{
	Node* newNode = (Node*)malloc(sizeof(Node));//newNode 이름을 가진 node를 동적 메모리로 할당
	newNode->key = key;//key에는 입력받은 값 삽입
	newNode->left = NULL;//노드의 left, right는 NULL로 초기화
	newNode->right = NULL;

	if (head->left == NULL) {//헤드의 left가 비었다면 새로운 노드를 넣어줌
		head->left = newNode;
		return 1;
	}
	Node* ptr = head->left;//head->left는루트임

	Node* parentNode = NULL;//부모노드 초기화
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)//ptr노드의 키값이 삽입된 값보다 작으면 ptr노드의 키값을 right에 삽입
			ptr = ptr->right;
		else
			ptr = ptr->left;//ptr노드의 키값이 더 크면 left에 삽입
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)//부모노드의 키값이 더 크면
		parentNode->left = newNode;//left에 newnode 삽입
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)//단말 노드 삭제
{
	if (head == NULL) {//head가 비었을때
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;//head 노드의 left가 루트이다


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {//ptr 노드의 키값이 삽입된 값과 같다면
			if(ptr->left == NULL && ptr->right == NULL) {//ptr 노드의 right, left 모두 NULL로 초기화

				/* root node case */
				if(parentNode == head)//부모노드와 헤드가 같다면
					head->left = NULL;//헤드의 left를 NULL로 초기화

				/* left node case or right case*/
				if(parentNode->left == ptr)//부모노드의 left와 ptr 노드가 같으면
					parentNode->left = NULL;//부모노드의 left를 NULL로 초기화
				else
					parentNode->right = NULL;//그렇지 않다면 right를 NULL로 초기화

				free(ptr);//해제
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)//현재 노드의 키값이 입력값보다 작으면
			ptr = ptr->right;//새로운 노드가 오른쪽 서브트리로 삽입됨
		else
			ptr = ptr->left;//아니라면 새로운 노드가 왼쪽 서브트리로 삽입됨


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)//검색 재귀
{
	if(ptr == NULL)
		return NULL;

	if(ptr->key < key)//ptr노드의 key 값이 key보다 작으면, right의 값을 검색 재귀
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)////ptr노드의 key 값이 key보다 크면, left의 값을 검색 재귀
		ptr = searchRecursive(ptr->left, key);

	/* if ptr->key == key */
	return ptr;

}
Node* searchIterative(Node* head, int key)//검색 반복
{
	/* root node */
	Node* ptr = head->left;//head노드의 left를 ptr노드에 대입

	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr;

		if(ptr->key < key) //ptr의 key값이 key 보다 작으면
			ptr = ptr->right; //right 값을 ptr에 대입
		else
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)//노드 해제
{
	if(ptr) {
		freeNode(ptr->left);//ptr의 left, right 모두 해제
		freeNode(ptr->right);
		free(ptr);//ptr 노드 해제
	}
}

int freeBST(Node* head)//이진탐색트리 해제
{

	if(head->left == head)//head의 left와 head노드가 같으면, head를 해제한다
	{
		free(head);
		return 1;
	}

	Node* p = head->left;//head의 left를 노드 p에 대입한뒤

	freeNode(p);//p를 해제하고

	free(head);//head를 해제한다
	return 1;
}