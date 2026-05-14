#ifndef Text_Processing_H
#define Text_Processing_H

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* ============================================================
   Colour codes (Windows CMD — WinAPI)
   ============================================================ */
#define COL_RESET 7
#define COL_TITLE 11
#define COL_HEADER 14
#define COL_OPTION 3
#define COL_OPTION_NUM 13
#define COL_INFO 2
#define COL_WARNING 12
#define COL_LABEL 6
#define COL_VALUE 9

/* ============================================================
   Abstract machine of Words Tree
   ============================================================ */
typedef struct WordNode {
    char val[100];
    struct WordNode* left;
    struct WordNode* right;
} WordNode;

typedef WordNode* Words;

Words AllocateWordNode(char* v);
void FreeWordNode(Words p);
Words InsertWord(char* v, Words R);
Words SearchWord(char* v, Words R);
void FreeWordTree(Words R);
void InorderWords(Words R);

/* ============================================================
   Abstract machine of Paragraphs Tree
   ============================================================ */
typedef struct ParagraphNode {
    int val;
    Words words;
    struct ParagraphNode* left;
    struct ParagraphNode* right;
} ParagraphNode;

typedef ParagraphNode* ParagraphNumber;

ParagraphNumber AllocateParagraphNode(int v);
void FreeParagraphNode(ParagraphNumber p);
ParagraphNumber InsertParagraph(int v, ParagraphNumber R);
ParagraphNumber SearchParagraph(int v, ParagraphNumber R);
void FreeParagraphTree(ParagraphNumber R);
void InorderParagraphs(ParagraphNumber R);
int CountParagraphs(ParagraphNumber R);

/* ============================================================
   Abstract machine of Files Tree
   ============================================================ */
typedef struct Node {
    char val[100];
    ParagraphNumber paragraphs;
    struct Node* left;
    struct Node* right;
} Node;

typedef Node* ptr;
typedef char element_type[100];

ptr AllocateNode(element_type v);
void FreeNode(ptr p);
char* NodeValue(ptr p);
ptr LC(ptr p);
ptr RC(ptr p);
void Ass_Node_Val(ptr p, element_type v);
void Ass_LC(ptr p, ptr q);
void Ass_RC(ptr p, ptr q);

/* ============================================================
   Abstract machine of Stacks
   ============================================================ */
struct StackNode {
    ptr val;
    struct StackNode* addr;
};
typedef struct StackNode* Stack;

void CreateStack(Stack* pp);
int EmptyStack(Stack s);
int Push(ptr x, Stack* pp);
int Pop(ptr* x, Stack* pp);

/* ============================================================
   Abstract machine of Linked List
   ============================================================ */
typedef struct WordListNode {
    char val[100];
    char separator;
    struct WordListNode* next;
} WordListNode;

typedef WordListNode* WordList;

void CreateWordList(WordList* pl);
int AddWordToList(char* val, char separator, WordList* pl);
void FreeWordList(WordList* pl);

/* ============================================================
   Core Functions
   ============================================================ */
ptr Search_by_inorder(ptr R, int n);
ParagraphNumber SearchParagraphByInorder(ParagraphNumber R, int n);
ptr Search(element_type v, ptr R);
ptr Insert(element_type v, ptr R);
void Inorder(ptr R);
ptr FindMin(ptr R);
void CopyParagraphs(ParagraphNumber src, ParagraphNumber* dest);
ptr DeleteNode(element_type v, ptr R);

void build_path(char* out, char* Name);
int file_existence(char* Name);
int Paragraphs_number(char* Name);
int SeparatorPriority(char sep);

Words ParseParagraph(char* filename, int paragraphNum, char* separators, bool caseSense, Words result, int types, int consecutiveWordsCount);

void FillWordsTree(ParagraphNumber R, char* filename, char* separators, bool caseSense, int selectType, int consecutiveWordsCount);
void ParseAllParagraphs(ptr files, int NumberFiles, char* separators, bool caseSense, int selectType, int consecutiveWordsCount);

int ExistsInParagraphTree(char* word, ParagraphNumber R);
int ExistsInAllParagraphNodes(char* word, ParagraphNumber R);
int ExistsInAllParagraphs(char* word, ptr files, int NumberFiles);

void IntersectionHelper(Words R, ptr files, int NumberFiles, Words* result);
void IntersectAllParagraphs(ParagraphNumber R, ptr files, int NumberFiles, Words* result);
Words Intersection(ptr files, int NumberFiles);

Words Union(ParagraphNumber R, char* filename, char* separators, bool caseSense, Words result, int types, int consecutiveWordsCount);

int ExistsInOtherParagraphs(char* word, ptr files, int NumberFiles);
void DifferenceHelper(Words R, Words B, Words* result);
int IsSubsetOf(Words A, Words B);
Words DifferenceAB(Words A, Words B);

int TotalParagraphsSelected(ptr AllFiles, int Number);

/* ============================================================
   UI / Display Functions
   ============================================================ */
void set_color(int c);
void print_separator(char ch, int n);
void print_title(void);
void print_status(bool CaseSense, char* Separators, int SelectType, int ConsecutiveWordsCount);
void print_files(ptr files, int NumberFiles);
void print_menu(void);
void pause_and_clear(void);
void msg_ok(char* text);
void msg_err(char* text);
void msg_info(char* text);

/* ============================================================
   Validation Functions
   ============================================================ */
int validate_op(ptr files, int NumberFiles, int SelectType);
int validate_two_paragraphs(ptr files, int NumberFiles, int SelectType);

#endif
