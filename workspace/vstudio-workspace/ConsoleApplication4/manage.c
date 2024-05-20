#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_BUFFER_SIZE 20

#pragma warning(disable:4996)
typedef struct Node {
	int front;
	int rear;
} Node;

Node* arr;
int size;

void init_list() {
	arr = (Node*)malloc(sizeof(Node) * (size + 1));
	arr[0].front = 0;
	arr[0].rear = 1;
	
	arr[size].front = 0;
	arr[size].rear = 0;

	for (int i = 1; i < size; i++) {
		arr[i].front = 0;
		arr[i].rear = i + 1;
	}
}

int is_exist(int n) {
	for (int i = 1; i <= size; i++)
		if (arr[i].front == n)
			return 1;
	return 0;
}

void insert(int n) {
	if (n < 0) {
		printf("Invalid data.\n");
		return;
	}

	if (is_exist(n)) {
		printf("Already exist.\n");
		return;
	}

	if (arr[0].rear == 0) {
		printf("List is full.\n");
		return;
	}

	int index = 0;
	int prev = 0;
	int next = arr[0].rear;

	if (arr[0].front == 0) {
		arr[next].front = n;
		arr[0].rear = arr[next].rear;
		arr[next].rear = 0;
		arr[0].front = next;
	}
	else {
		int next = arr[0].front;
		while (arr[next].rear != 0) {
			if (n >= arr[next].front) {
				prev = next;
				next = arr[next].rear;
			}
			else {
				if (next == arr[0].front)
					arr[0].front = arr[0].rear;
				index = arr[0].rear;
				arr[0].rear = arr[index].rear;
				arr[index].front = n;

				if (prev != 0)
					arr[prev].rear = index;
				arr[index].rear = next;

				return;
			}
		}

		index = arr[0].rear;
		arr[0].rear = arr[index].rear;
		if (n > arr[next].front) {
			arr[index].front = n;
			arr[index].rear = 0;
			arr[next].rear = index;
		}
		else {
			arr[index].front = n;
			arr[index].rear = next;
			
			if (prev == 0)
				arr[prev].front = index;
			else
				arr[prev].rear = index;
			arr[next].rear = 0;
		}
	}
}

void _remove(int n) {
	if (n == 0) {
		printf("Invalid input.\n");
		return;
	}

	if (arr[0].front == 0) {
		printf("Not exist.\n");
		return;
	}

	if (n > 0) {
		if (!is_exist(n)) {
			printf("Not exist.\n");
			return;
		}

		int prev = 0;
		int next = arr[0].front;

		if (arr[next].front == n) {
			arr[0].front = arr[next].rear;
			arr[next].front = 0;

			int index = next;
			next = arr[0].rear;

			if (next == 0) {
				arr[index].rear = 0;
				arr[0].rear = index;
				return;
			}

			while (arr[next].rear != 0) {
				prev = next;
				next = arr[next].rear;
			}
			
			arr[next].rear = index;
			arr[index].rear = 0;
			
			return;
		}

		while (arr[next].rear != 0) {
			if (arr[next].front == n) {
				arr[prev].rear = arr[next].rear;
				arr[next].front = 0;

				int index = next;
				next = arr[0].rear;
				while (arr[next].rear != 0) {
					prev = next;
					next = arr[next].rear;
				}

				arr[next].rear = index;
				arr[index].rear = 0;

				return;
			}
			prev = next;
			next = arr[next].rear;
		}

		arr[prev].rear = 0;
		arr[next].front = 0;

		int index = next;
		next = arr[0].rear;
		while (arr[next].rear != 0) {
			prev = next;
			next = arr[next].rear;
		}

		arr[next].rear = index;

		return;
	}
	else {
		n *= -1;

		int prev = 0;
		int next = arr[0].front;

		for (int i = 1; i < n; i++) {
			if (arr[next].rear == 0) {
				printf("Invalid order.\n");
				return;
			}
			prev = next;
			next = arr[next].front;
		}

		if (arr[next].front == 0) {
			printf("Invalid order.\n");
			return;
		}

		arr[next].front = 0;
		if (prev == 0) {
			arr[prev].front = arr[next].rear;
		}
		else 
			arr[prev].rear = arr[next].rear;

		int index = next;
		next = arr[0].rear;
		while (arr[next].rear != 0) {
			prev = next;
			next = arr[next].rear;
		}

		arr[next].rear = index;
		arr[index].rear = 0;
	}
}

void modify(int n, int var) {
	_remove(n);
	insert(var);
}

void search(int n) {
	if (n == 0) {
		printf("Invalid input.\n");
		return;
	}

	if (arr[0].front == 0) {
		printf("Not exist.\n");
		return;
	}

	if (n > 0) {
		if (!is_exist(n)) {
			printf("Not exist.\n");
			return;
		}

		int order = 1;
		int next = arr[0].front;

		while (arr[next].front != n) {
			order++;
			next = arr[next].rear;
		}
		if (order % 10 == 1)
			printf("[ %d ] is in %dst.\n", n, order);
		else if (order % 10 == 2)
			printf("[ %d ] is in %dnd.\n", n, order);
		else if (order % 10 == 3)
			printf("[ %d ] is in %drd.\n", n, order);
		else
			printf("[ %d ] is in %dth.\n", n, order);
	}
	else {
		n *= -1;

		int prev = 0;
		int next = arr[0].front;

		for (int i = 1; i < n; i++) {
			if (arr[next].rear == 0) {
				printf("Invalid order.\n");
				return;
			}
			prev = next;
			next = arr[next].front;
		}

		if (arr[next].front == 0) {
			printf("Invalid order.\n");
			return;
		}

		if (n % 10 == 1)
			printf("%dst data is [ %d ].\n", n, arr[next].front);
		else if (n % 10 == 2)
			printf("%dnd data is [ %d ].\n", n, arr[next].front);
		else if (n % 10 == 3)
			printf("%drd data is [ %d ].\n", n, arr[next].front);
		else
			printf("%dth data is [ %d ].\n", n, arr[next].front);
	}
}

void list() {
	int next = arr[0].front;

	if (next == 0) {
		printf("List is empty.\n");
		return;
	}

	printf("[ List ] ");
	while (arr[next].rear != 0) {
		printf("%d ", arr[next].front);
		next = arr[next].rear;
	}

	printf("%d\n", arr[next].front);
}

int main(int argc, char* argv[]) {
	FILE* fp;
	char file[MAX_BUFFER_SIZE];
	
	int type;
	if (argc == 2) {
		strcpy(file, argv[1]);
		fp = fopen(file, "rb");
		type = 1;

		fseek(fp, 0, SEEK_END);
		long file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		init_list(file_size / sizeof(Node*));
		if (fread(arr, sizeof(Node*), file_size / sizeof(Node*), fp) != file_size / sizeof(Node*)) {
			printf("File read error.\n");
			return -1;
		}
	}
	else if (argc == 3) {
		size = atoi(argv[2]);

		if (size <= 0) {
			printf("Invalid size.\n");
			return -1;
		}

		strcpy(file, argv[1]);
		fp = fopen(file, "wb");

		init_list(size);
		type = 2;
	}
	else {
		printf("Usage: manage [storage] [size(optional)]\n");
		return 0;
	}
	
	while (1) {
		printf("%% ");

		char command;
		scanf(" %c", &command);

		int input, var;
		switch (command) {
		case 'i':
			scanf(" %d", &input);
			if (type == 1) {
				printf("File is opened by read mode.");
				break;
			}
			insert(input);
			break;

		case 'r':
			scanf(" %d", &input);
			if (type == 1) {
				printf("File is opened by read mode.");
				break;
			}
			_remove(input);
			break;

		case 'm':
			scanf(" %d", &input);
			scanf(" %d", &var);
			if (type == 1) {
				printf("File is opened by read mode.");
				break;
			}
			modify(input, var);
			break;

		case 's':
			scanf(" %d", &input);
			search(input);
			break;

		case 'l':
			list();
			break;

		case 'q':
			if (type == 2) {
				fwrite(arr, sizeof(Node *), size, fp);
			}
			fclose(fp);
			free(arr);
			return 0;

		default:
			printf("Wrong command.\n");
			break;
		}

		printf("\n");
	}
}