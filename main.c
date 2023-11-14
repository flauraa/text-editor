#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

FILE* file;

typedef struct Node
{
	struct Node* next;
	char c;
}Node;

Node* begin;
Node* end;

//creates a node, uploads the data
Node* create_node(char c)
{
	Node* node = malloc(sizeof(Node));
	*node = (Node){NULL, c};
	return node;
}

//receives as a parameter a node pointer
void add_node(Node* node)
{
	if(!begin) end = begin = node;
	else end = end->next = node;
}

//deletes the last caharacter
void delete_end(void)
{
	if(begin == end)
	{
		free(begin);
		end = begin = NULL;
		return;
	}
	Node* previous = NULL; 
	for(Node* it = begin; it != end; it = it->next)
		previous = it;
	free(end);
	end = previous;
	end->next = NULL;
}

//prints the list with the chosen color modfications
void print_list(void)
{
	int nr_line = 1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("%6d | ", nr_line++);
	char buffer[200] = "";
	for(Node* it = begin; it != NULL; it = it->next)
	{
		buffer[0] = 0;
		if(strchr(" \n\t", it->c)) 
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			printf("%c", it->c);
			if(it->c == '\n') 
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("%6d | ", nr_line++);
			}
			continue;
		}

		for(Node* buff = it; buff != NULL && !strchr(" \n\t", buff->c) ; buff = buff->next)
		{
			it = buff;
			sprintf(buffer, "%s%c", buffer, buff->c);
		}

		if(!strcmp(buffer, "int") || !strcmp(buffer, "float") || !strcmp(buffer, "double") || !strcmp(buffer, "char")) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); //magenta
		else if(strstr("= () [] {} ;", buffer)) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //green
		else if(strstr("+ - * / & ! || && < > <= >= != ==", buffer)) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //blue
		else if(!strcmp(buffer, "main") || !strcmp(buffer, "if") || !strcmp(buffer, "for") || !strcmp(buffer, "while"))SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); //cyan
		else if(!strcmp(buffer, "#include") || !strcmp(buffer, "<stdio.h>")) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //red
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //white
		printf("%s", buffer);
	}
}

void backspace(void)
{
	delete_end();
}

//saves the content in a file
void save_file(void)
{
	file = fopen("fisier.txt", "w");
	for(Node* it = begin; it != NULL; it = it->next)
		fprintf(file, "%c", it->c);
	fclose(file);
	exit(0);
}

//reads character by character
int read_c(void)
{
	char c = getch();

	if(c == 13) c = '\n'; //enter
	else if(c == 3) save_file();  //CTRL C
	else if(c == 8) {backspace(); return 0;} //backspace

	add_node(create_node(c));
	return 1;
}

//prints the list
void print_end(void)
{
	printf("%c", end->c);
}

int main()
{
	system("cls");
	print_list();
	while(1)
	{
		read_c();
		system("cls");
		print_list();
	}
}