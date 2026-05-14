#include "Text_Processing.h"

Words AllocateWordNode(char* v) {
    Words p = (Words)malloc(sizeof(WordNode));
    if (p != NULL) {
        strcpy(p->val, v);
        p->left = NULL;
        p->right = NULL;
    }
    return p;
}

void FreeWordNode(Words p) { free(p); }

Words InsertWord(char* v, Words R) {
    if (R == NULL) return AllocateWordNode(v);
    if (strcmp(v, R->val) < 0) R->left = InsertWord(v, R->left);
    else if (strcmp(v, R->val) > 0) R->right = InsertWord(v, R->right);
    return R;
}

Words SearchWord(char* v, Words R) {
    if (R == NULL) return NULL;
    if (strcmp(v, R->val) == 0) return R;
    if (strcmp(v, R->val) < 0) return SearchWord(v, R->left);
    else return SearchWord(v, R->right);
}

//en post-order
void FreeWordTree(Words R) {
    if (R == NULL) return;
    FreeWordTree(R->left);
    FreeWordTree(R->right);
    FreeWordNode(R);
}

// Print in inorder
void InorderWords(Words R) {
    if (R == NULL) return;
    InorderWords(R->left);
    printf("%s \n", R->val);
    InorderWords(R->right);
}

ParagraphNumber AllocateParagraphNode(int v) {
    ParagraphNumber p = (ParagraphNumber)malloc(sizeof(ParagraphNode));
    if (p != NULL) {
        p->val = v;
        p->words = NULL;
        p->left = NULL;
        p->right = NULL;
    }
    return p;
}

void FreeParagraphNode(ParagraphNumber p) {
    if (p != NULL) {
        FreeWordTree(p->words);
        free(p);
    }
}

ParagraphNumber InsertParagraph(int v, ParagraphNumber R) {
    if (R == NULL) return AllocateParagraphNode(v);
    if (v < R->val) R->left = InsertParagraph(v, R->left);
    else if (v > R->val) R->right = InsertParagraph(v, R->right);
    return R;
}

ParagraphNumber SearchParagraph(int v, ParagraphNumber R) {
    if (R == NULL) return NULL;
    if (v == R->val) return R;
    if (v < R->val) return SearchParagraph(v, R->left);
    else return SearchParagraph(v, R->right);
}

void FreeParagraphTree(ParagraphNumber R) {
    if (R == NULL) return;
    FreeParagraphTree(R->left);
    FreeParagraphTree(R->right);
    FreeParagraphNode(R);
}

void InorderParagraphs(ParagraphNumber R) {
    if (R == NULL) return;
    InorderParagraphs(R->left);
    printf("%d ", R->val);
    InorderParagraphs(R->right);
}

// Total paragraphs selected
int CountParagraphs(ParagraphNumber R) {
    if (R == NULL) return 0;
    return 1 + CountParagraphs(R->left) + CountParagraphs(R->right);
}

ptr AllocateNode(element_type v) {
    ptr p = (ptr)malloc(sizeof(Node));
    if (p != NULL) {
        strcpy(p->val, v);
        p->paragraphs = NULL;
        p->left = NULL;
        p->right = NULL;
    }
    return p;
}

void FreeNode(ptr p) {
    if (p != NULL) {
        FreeParagraphTree(p->paragraphs);
        free(p);
    }
}

char* NodeValue(ptr p) { return p->val; }

ptr LC(ptr p) { return p->left; }

ptr RC(ptr p) { return p->right; }

void Ass_Node_Val(ptr p, element_type v) { if (p != NULL) strcpy(p->val, v); }

void Ass_LC(ptr p, ptr q) { if (p != NULL) p->left = q; }

void Ass_RC(ptr p, ptr q) { if (p != NULL) p->right = q; }


// This stack stores file node pointers (ptr) and is used by Search_by_inorder to perform an iterative in-order traversal of the files BST without recursion.

void CreateStack(Stack* pp) { *pp = NULL; }

int EmptyStack(Stack s) { return (s == NULL); }

int Push(ptr x, Stack* pp) {
    struct StackNode* q = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (q == NULL) return 0;
    q->val = x;
    q->addr = *pp;
    *pp = q;
    return 1;
}

int Pop(ptr* x, Stack* pp) {
    if (EmptyStack(*pp)) return 0;
    struct StackNode* q = *pp;
    *x = (*pp)->val;
    *pp = (*pp)->addr;
    free(q);
    return 1;
}

// ── Word linked list ──────────────────────────────────────────────────────────
// A simple singly-linked list used exclusively by ParseParagraph (case 3) to collect individual words of a line together with the separator that preceded them, before deciding which groups of consecutive words are valid and can be inserted into the words BST.

void CreateWordList(WordList* pl) { *pl = NULL; }

int AddWordToList(char* val, char separator, WordList* pl) {
    WordListNode* p = (WordListNode*)malloc(sizeof(WordListNode));
    strcpy(p->val, val);
    p->separator = separator;
    p->next = NULL;
    // ajouter en fin de liste
    if (*pl == NULL) {
        *pl = p;
    } else {
        WordListNode* current = *pl;
        while (current->next != NULL) current = current->next;
        current->next = p;
    }
    return 1;
}

void FreeWordList(WordList* pl) {
    while (*pl != NULL) {
        WordListNode* temp = *pl;
        *pl = (*pl)->next;
        free(temp);
    }
}

// ── Tree traversal and BST operations ────────────────────────────────────────

// Search the nth node in a tree
ptr Search_by_inorder(ptr R, int n) {
    Stack s;
    CreateStack(&s);
    ptr current = R;
    int count = 0;

    while (current != NULL || !EmptyStack(s)) {
        while (current != NULL) {
            Push(current, &s);
            current = LC(current);
        }
        Pop(&current, &s);
        count++;
        if (count == n) {
            return current;
        }
        current = RC(current);
    }
    return NULL;
}

// Returns the n-th paragraph node in the paragraphs BST when visited in
// in-order (ascending numeric) sequence. Uses a fixed-size array as a stack
// instead of the linked-list Stack used by Search_by_inorder. Counting starts
// at 1. Returns NULL if n exceeds the number of nodes in the tree.
// This allows callers to refer to paragraphs by their selection order (1st
// selected, 2nd selected, ...) rather than by their actual paragraph number.
ParagraphNumber SearchParagraphByInorder(ParagraphNumber R, int n) {

    ParagraphNumber stack[100];
    int top = 0;

    ParagraphNumber current = R;
    int count = 0;

    while (current != NULL || top > 0) {
        while (current != NULL) {
            stack[top++] = current;
            current = current->left;
        }
        current = stack[--top];
        count++;
        if (count == n) return current;
        current = current->right;
    }
    return NULL;
}

ptr Search(element_type v, ptr R) {
    if (R == NULL) {
        return NULL;
    }
    if (strcmp(v, R->val) == 0) {
        return R;
    }
    if (strcmp(v, R->val) < 0) {
        return Search(v, LC(R));
    }
    else {
        return Search(v, RC(R));
    }
}

ptr Insert(element_type v, ptr R) {
    if (R == NULL) {
        return AllocateNode(v);
    }
    if (strcmp(v, R->val) < 0) {
        Ass_LC(R, Insert(v, LC(R)));
    }
    else if (strcmp(v, R->val) > 0) {
        Ass_RC(R, Insert(v, RC(R)));
    }
    return R;
}

// Prints filenames in inorder way
void Inorder(ptr R) {
    if (R == NULL) return;
    Inorder(LC(R));
    printf("%s\t", NodeValue(R));
    Inorder(RC(R));
}

// Or how we saw it in class nextInorder
ptr FindMin(ptr R) {
    while (LC(R) != NULL) R = LC(R);
    return R;
}

// Needed when delete a Paragraph Node
void CopyParagraphs(ParagraphNumber src, ParagraphNumber* dest) {
    if (src == NULL) return;
    *dest = InsertParagraph(src->val, *dest);
    SearchParagraph(src->val, *dest)->words = src->words;
    CopyParagraphs(src->left, dest);
    CopyParagraphs(src->right, dest);
}

// Seen in class, however here we added copy paragraphs to replace the deleted paragraph if needed
ptr DeleteNode(element_type v, ptr R) {
    if (Search(v, R) == NULL) {
        printf("%s not found in the tree\n", v);
        return R;
    }
    if (strcmp(v, R->val) < 0) {
        Ass_LC(R, DeleteNode(v, LC(R)));
    } else if (strcmp(v, R->val) > 0) {
        Ass_RC(R, DeleteNode(v, RC(R)));
    } else {
        if (LC(R) == NULL && RC(R) == NULL) {
            // Leaf node: simply free and return NULL
            FreeNode(R);
            return NULL;
        } else if (LC(R) == NULL) {
            // Only a right child: bypass R and return it
            ptr temp = RC(R);
            FreeNode(R);
            return temp;
        } else if (RC(R) == NULL) {
            // Only a left child: bypass R and return it
            ptr temp = LC(R);
            FreeNode(R);
            return temp;
        } else {
            // Two children: replace R with its in-order successor (smallest in right subtree),
            // transfer the successor's paragraphs to R, then delete the successor
            ptr temp = FindMin(RC(R));
            Ass_Node_Val(R, temp->val);
            FreeParagraphTree(R->paragraphs);
            R->paragraphs = NULL;
            // copie le BST paragraphes du successeur
            void CopyParagraphs(ParagraphNumber src, ParagraphNumber* dest);
            CopyParagraphs(temp->paragraphs, &R->paragraphs);
            Ass_RC(R, DeleteNode(temp->val, RC(R)));
        }
    }
    return R;
}

// Checks if a file exist
int file_existence(char* Name) {
    char FullPath[256];
    sprintf(FullPath, "File_Texts/%s", Name);
    FILE* fp = fopen(FullPath, "r");
    if (fp == NULL) return 0;
    fclose(fp);
    return 1;
}

// Counts number of paragraph of a file.
int Paragraphs_number(char* Name) {
    char FullPath[256];
    bool New_line = false;
    sprintf(FullPath, "File_Texts/%s", Name);
    FILE* fp = fopen(FullPath, "r");
    if (fp == NULL) return 0;

    int NumberParagraphs = 0;
    int character;
    bool lastWasNewline = false;
    bool inParagraph = false;
    while ((character = fgetc(fp)) != EOF) {
        if (character == '\n') {
            if (lastWasNewline && inParagraph) {
                NumberParagraphs++;
                inParagraph = false;
            }
            lastWasNewline = true;
        } else {
            lastWasNewline = false;
            inParagraph = true;
        }
    }
    if (inParagraph) NumberParagraphs++;
    fclose(fp);
    return NumberParagraphs;
}

// Needed in consecutive words, if any word is preceeded by "." or "!" or "?" then they are not successive words
int SeparatorPriority(char sep) {
    if (sep == '.' || sep == '!' || sep == '?') {
        return 2;
    } else {
        return 1;
    }
}

// Parse paragraph and put them inside nodes, these nodes will be used to make the operations
Words ParseParagraph(char* filename, int paragraphNum, char* separators, bool caseSense, Words result, int types, int consecutiveWordsCount) {
    // Open file
    char FullPath[256];
    sprintf(FullPath, "File_Texts/%s", filename);
    FILE* fp = fopen(FullPath, "r");
    if (fp == NULL) return result;

    // Skip until the right paragraph (paragraphs separated by \n\n)
    int currentParagraph = 1;
    int character;
    bool lastWasNewline = false;
    bool inParagraph = false;
    while (currentParagraph < paragraphNum) {
        character = fgetc(fp);
        if (character == EOF) { fclose(fp); return result; }
        if (character == '\n') {
            if (lastWasNewline && inParagraph) {
                currentParagraph++;
                inParagraph = false;
            }
            lastWasNewline = true;
        } else {
            lastWasNewline = false;
            inParagraph = true;
        }
    }

    // Skip any leading newlines before the paragraph content
    while ((character = fgetc(fp)) == '\n');

    char word[100];
    int length = 0;

    while (character != EOF && character != '\n') {
        switch (types) {
            case 1: // Letters
                if (!strchr(separators, character)) {
                    word[0] = caseSense ? character : tolower(character);
                    word[1] = '\0';
                    result = InsertWord(word, result);
                }
            break;

            case 2: // Words
                if (strchr(separators, character)) {
                    if (length > 0) {
                        word[length] = '\0';
                        result = InsertWord(word, result);
                        length = 0;
                    }
                } else {
                    if (caseSense) {
                        word[length++] = character;
                    }
                    else {
                        word[length++] = tolower(character);
                    }
                }
            break;

            case 3: // Consecutive words
            {
                WordList wordList = NULL;
                char currentWord[100];
                int currentLength = 0;
                char lastSeparator = '\0';

                char ch = character;
                while (ch != EOF && ch != '\n') {
                    if (strchr(separators, ch)) {
                        if (currentLength > 0) {
                            currentWord[currentLength] = '\0';
                            AddWordToList(currentWord, lastSeparator, &wordList);
                            currentLength = 0;
                            lastSeparator = ch;
                        } else {
                            // Check if there is a separator that doesn't let words to be consecutive (as seen in ReadMe.md)
                            if (SeparatorPriority(ch) > SeparatorPriority(lastSeparator))
                                lastSeparator = ch;
                        }
                    } else {
                        if (caseSense)
                            currentWord[currentLength++] = ch;
                        else
                            currentWord[currentLength++] = tolower(ch);
                    }
                    ch = fgetc(fp);
                }

                // Last word in consecutive words
                if (currentLength > 0) {
                    currentWord[currentLength] = '\0';
                    AddWordToList(currentWord, lastSeparator, &wordList);
                }

                // Checks the separators and then insert the the whole consecutive words inside the tree.
                WordListNode* window = wordList;
                while (window != NULL) {
                    WordListNode* check = window;
                    int count = 0;
                    bool validWindow = true;

                    while (check != NULL && count < consecutiveWordsCount) {
                        if (count > 0 && SeparatorPriority(check->separator) == 2)
                        validWindow = false;
                        count++;
                        check = check->next;
                    }

                    if (count == consecutiveWordsCount && validWindow) {
                        char suite[1000];
                        suite[0] = '\0';
                        WordListNode* current = window;
                        for (int w = 0; w < consecutiveWordsCount; w++) {
                            strcat(suite, current->val);
                            if (w < consecutiveWordsCount - 1) strcat(suite, " ");
                            current = current->next;
                        }
                        result = InsertWord(suite, result);
                    }

                    window = window->next;
                }

                FreeWordList(&wordList);
            }
            break;

            case 4: // Sentences
            {
                char sentence[1000];
                int sentenceLength = 0;

                char ch = character;
                while (ch != EOF && ch != '\n') {
                    if (ch == '.' || ch == '!' || ch == '?') {
                        // End of sentence, we insert it if it is non null
                        if (sentenceLength > 0) {
                            sentence[sentenceLength] = '\0';
                            result = InsertWord(sentence, result);
                            sentenceLength = 0;
                        }
                    } else {
                        if (caseSense)
                            sentence[sentenceLength++] = ch;
                        else
                            sentence[sentenceLength++] = tolower(ch);
                    }
                    ch = fgetc(fp);
                }

                // If last sentence doesn't finish with a dot or ! or ?
                if (sentenceLength > 0) {
                    sentence[sentenceLength] = '\0';
                    result = InsertWord(sentence, result);
                }
            }
            break;
        }
        character = fgetc(fp);
    }

    fclose(fp);
    return result;
}

// Traverses the paragraph BST in-order and for each paragraph node calls ParseParagraph to (re)build its words BST from the actual file content.
// All parsing parameters are forwarded directly to ParseParagraph without modification
void FillWordsTree(ParagraphNumber R, char* filename, char* separators, bool caseSense, int selectType, int consecutiveWordsCount) {
    if (R == NULL) return;
    FillWordsTree(R->left, filename, separators, caseSense, selectType, consecutiveWordsCount);
    FreeWordTree(R->words);  // on libère l'ancien BST si existant
    R->words = ParseParagraph(filename, R->val, separators, caseSense, NULL, selectType, consecutiveWordsCount);
    FillWordsTree(R->right, filename, separators, caseSense, selectType, consecutiveWordsCount);
}

// Iterates over all NumberFiles loaded files (accessed by in-order position) and calls FillWordsTree on each file's paragraph BST to (re)parse every selected paragraph. This is called at the start of each set operation (Union, Intersection, Difference, etc.) to ensure the words trees reflect the current parsing settings (type, separators, case)
void ParseAllParagraphs(ptr files, int NumberFiles, char* separators, bool caseSense, int selectType, int consecutiveWordsCount) {
    for (int i = 1; i <= NumberFiles; i++) {
        ptr fileNode = Search_by_inorder(files, i);
        FillWordsTree(fileNode->paragraphs, NodeValue(fileNode), separators, caseSense, selectType, consecutiveWordsCount);
    }
}

// Returns 1 if the given word exists in every paragraph node of the paragraphs BST, 0 otherwise
int ExistsInAllParagraphNodes(char* word, ParagraphNumber R) {
    if (R == NULL) return 1;
    if (SearchWord(word, R->words) == NULL) return 0;
    return ExistsInAllParagraphNodes(word, R->left) && ExistsInAllParagraphNodes(word, R->right);
}

// Returns 1 if the given word appears in at least one selected paragraph of every loaded file, 0 otherwise
int ExistsInAllParagraphs(char* word, ptr files, int NumberFiles) {
    for (int i = 1; i <= NumberFiles; i++) {
        ptr fileNode = Search_by_inorder(files, i);
        if (!ExistsInAllParagraphNodes(word, fileNode->paragraphs))  // ← TOUS les paragraphes
            return 0;
    }
    return 1;
}

// Traverses the words BST R in-order and for each word decides whether to add
// it to *result based on how many files are loaded:
//   - If NumberFiles == 1: the word must appear in every paragraph of that file (checked by ExistsInAllParagraphNodes).
//   - If NumberFiles >= 2: the word must appear in at least one paragraph of every loaded file (checked by ExistsInAllParagraphs).
// Words that pass the check are inserted into the *result BST.
void IntersectionHelper(Words R, ptr files, int NumberFiles, Words* result) {
    if (R == NULL) return;
    IntersectionHelper(R->left, files, NumberFiles, result);
    if (NumberFiles == 1) {
        ptr fileNode = Search_by_inorder(files, 1);
        if (ExistsInAllParagraphNodes(R->val, fileNode->paragraphs))
            *result = InsertWord(R->val, *result);
    } else {
        if (ExistsInAllParagraphs(R->val, files, NumberFiles))
            *result = InsertWord(R->val, *result);
    }
    IntersectionHelper(R->right, files, NumberFiles, result);
}

// Traverses the paragraph BST in-order and calls IntersectionHelper on the words BST of each paragraph node, accumulating results into *result
void IntersectAllParagraphs(ParagraphNumber R, ptr files, int NumberFiles, Words* result) {
    if (R == NULL) return;
    IntersectAllParagraphs(R->left, files, NumberFiles, result);
    IntersectionHelper(R->words, files, NumberFiles, result);
    IntersectAllParagraphs(R->right, files, NumberFiles, result);
}

// Entry point for computing the intersection of all loaded files.
Words Intersection(ptr files, int NumberFiles) {
    ptr firstFile = Search_by_inorder(files, 1);
    Words result = NULL;
    IntersectAllParagraphs(firstFile->paragraphs, files, NumberFiles, &result);
    return result;
}

// Builds the union of all words across the selected paragraphs of a single file by recursively traversing the paragraphs BST inorder and calling ParseParagraph on each paragraph, merging the results in result
Words Union(ParagraphNumber R, char* filename, char* separators, bool caseSense, Words result, int types, int consecutiveWordsCount) {
    if (R == NULL) return result;
    result = Union(R->left, filename, separators, caseSense, result, types, consecutiveWordsCount);
    result = ParseParagraph(filename, R->val, separators, caseSense, result, types, consecutiveWordsCount);
    result = Union(R->right, filename, separators, caseSense, result, types, consecutiveWordsCount);
    return result;
}

// Traverses the words BST R in-order and adds each word to *result only if that word is absent from the words BST B
void DifferenceHelper(Words R, Words B, Words* result) {
    if (R == NULL) return;
    DifferenceHelper(R->left, B, result);
    if (SearchWord(R->val, B) == NULL)
        *result = InsertWord(R->val, *result);
    DifferenceHelper(R->right, B, result);
}

// Returns 1 if every word in words BST A also exists in words BST B (A ⊆ B), 0 otherwise. An empty set A (A == NULL) is always a subset of any set B
int IsSubsetOf(Words A, Words B) {
    if (A == NULL) return 1; // ensemble vide => toujours sous-ensemble
    if (SearchWord(A->val, B) == NULL) return 0; // un mot de A absent de B
    return IsSubsetOf(A->left, B) && IsSubsetOf(A->right, B);
}

// Returns a new words BST containing words that are in A but not in B (A − B)
Words DifferenceAB(Words A, Words B) {
    Words result = NULL;
    DifferenceHelper(A, B, &result);
    return result;
}

// Verify if at least 1 paragraph has been selected
int TotalParagraphsSelected(ptr AllFiles, int Number) {
    int total = 0;
    for (int i = 1; i <= Number; i++) {
        ptr node = Search_by_inorder(AllFiles, i);
        total += CountParagraphs(node->paragraphs);
    }
    return total;
}

// ============================================================
//   Colours  (Windows CMD — WinAPI)
// ============================================================

// Sets the Windows console text colour using the predefined colour codes above
void set_color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Prints a horizontal separator line of n repetitions of character ch
void print_separator(char ch, int n) {
    set_color(COL_HEADER);
    for (int i = 0; i < n; i++) putchar(ch);
    putchar('\n');
    set_color(COL_RESET);
}

// Prints the application title banner
void print_title() {
    print_separator('=', 55);
    set_color(COL_TITLE);
    printf("       TEXT PROCESSING TOOL  v1.0\n");
    set_color(8);  // dark grey
    printf("    Made by AIT MESSAOUD Yanis & SEDDARI Mohamed Louay\n");
    print_separator('=', 55);
    set_color(COL_RESET);
}

// Prints the current session settings: case sensitivity, separators, and selected type
void print_status(bool CaseSense, char* Separators, int SelectType, int ConsecutiveWordsCount) {
    print_separator('-', 55);

    set_color(COL_LABEL);
    printf("  Case Sensitive : ");
    set_color(CaseSense ? COL_INFO : COL_WARNING);
    printf("%s\n", CaseSense ? "ON" : "OFF");

    set_color(COL_LABEL);
    printf("  Separators     : ");
    set_color(COL_VALUE);
    printf("%s\n", Separators);

    if (SelectType != 0) {
        set_color(COL_LABEL);
        printf("  Current type   : ");
        set_color(COL_VALUE);
        switch (SelectType) {
            case 1:
                printf("Letters\n");
            break;
            case 2:
                printf("Words\n");
            break;
            case 3:
                printf("Consecutive words (%d)\n", ConsecutiveWordsCount);
            break;
            case 4:
                printf("Sentences\n");
            break;
        }
    }

    set_color(COL_RESET);
    print_separator('-', 55);
}

// Prints the list of loaded files along with their selected paragraph numbers
void print_files(ptr files, int NumberFiles) {
    if (NumberFiles == 0) return;

    set_color(COL_LABEL);
    printf("  Files added    : ");
    set_color(COL_VALUE);
    Inorder(files);
    printf("\n");

    for (int i = 1; i <= NumberFiles; i++) {
        ptr node = Search_by_inorder(files, i);
        if (node->paragraphs != NULL) {
            set_color(COL_INFO);
            printf("    > %s", NodeValue(node));
            set_color(8);
            printf("  (paragraphs: ");
            set_color(COL_VALUE);
            InorderParagraphs(node->paragraphs);
            set_color(8);
            printf(")\n");
        }
    }

    set_color(COL_RESET);
    print_separator('-', 55);
}

// Prints the main operations menu with numbered options
void print_menu() {
    set_color(COL_HEADER);
    printf("\n  OPERATIONS\n");
    print_separator('-', 55);

    // Set console to UTF-8 (optional, helps with some characters)
    SetConsoleOutputCP(CP_UTF8);


    int nums[]  = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    char* ops[] = {
        "Change Case Sensitivity",
        "Change Separators",
        "Select type (letters / words / …)",
        "Add a file",
        "Delete a file",
        "Select paragraphs",
        "Union",
        "Intersection",
        "Difference",
        "Subset",
        "Complement",
        "All operations",
        "Exit"
    };

    for (int i = 0; i < 13; i++) {
        set_color(COL_OPTION_NUM);
        printf("  %2d. ", nums[i]);
        set_color(i == 12 ? COL_WARNING : COL_OPTION);
        printf("%s\n", ops[i]);
    }

    print_separator('-', 55);
    set_color(COL_HEADER);
    printf("  Choice : ");
    set_color(COL_VALUE);
}

//Pause to let the user see the results
void pause_and_clear() {
    int ch;
    set_color(8);
    printf("\n  Press ENTER to continue...");
    set_color(COL_RESET);
    while ((ch = getchar()) != '\n' && ch != EOF) {}
    getchar();
    system("cls");
}

//print errors or success messages
void msg_ok(char* text) {
    set_color(COL_INFO);
    printf("\n  [OK]  %s\n", text);
    set_color(COL_RESET);
}

void msg_err(char* text) {
    set_color(COL_WARNING);
    printf("\n  [!!]  %s\n", text);
    set_color(COL_RESET);
}

void msg_info(char* text) {
    set_color(COL_LABEL);
    printf("\n  [>]   %s\n", text);
    set_color(COL_RESET);
}

// Returns 1 if everything is ready, 0 otherwise
int validate_op(ptr files, int NumberFiles, int SelectType) {
    int ok = 1;

    if (NumberFiles == 0) {
        msg_err("Add at least one file.");
        ok = 0;
    }

    if (TotalParagraphsSelected(files, NumberFiles) == 0) {
        msg_err("Select at least one paragraph.");
        ok = 0;
    }

    if (SelectType == 0) {
        msg_err("Select a type first.");
        ok = 0;
    }

    return ok;
}

// Validation for operations that need exactly 2 paragraphs (Difference, Subset, All)
int validate_two_paragraphs(ptr files, int NumberFiles, int SelectType) {

    if (!validate_op(files, NumberFiles, SelectType)) {
        return 0;
    }

    if (TotalParagraphsSelected(files, NumberFiles) != 2) {
        msg_err("This operation needs exactly 2 paragraphs selected (A and B).");
        return 0;
    }

    return 1;
}

int main() {
    /* ── Variables : Ce que fait chaque varible ─────────────────────────────────────
     * files          : racine du BST des fichiers chargés (trié alphabétiquement)
     * NumberFiles    : nombre de fichiers actuellement dans le BST
     * i              : compteur générique (boucles, fichiers, paragraphes)
     * choice         : option saisie par l'utilisateur dans le menu principal
     * paragraph      : numéro de paragraphe saisi lors de la sélection
     * SelectType     : mode d'analyse (0=non défini, 1=lettres, 2=mots, 3=mots consécutifs, 4=phrases)
     * ConsecutiveWordsCount : nombre N de mots consécutifs (utilisé si SelectType==3)
     * FileName       : buffer pour le nom de fichier saisi
     * CaseSensitive  : buffer pour la réponse Y/N à la question de casse
     * Separators     : chaîne des caractères séparateurs utilisés lors du parsing
     * CaseSense      : true = on distingue majuscules/minuscules, false = non
     * stop           : drapeau booléen pour sortir des boucles de saisie multi-fichiers
     * ─────────────────────────────────────────────────────────────────────── */
    ptr files = NULL;
    int NumberFiles = 0, i, choice, paragraph;
    int SelectType = 0, ConsecutiveWordsCount = 0;
    char FileName[100], CaseSensitive[100], Separators[50];
    bool CaseSense = false, stop;

    /* Séparateurs par défaut : espace + ponctuation courante. */
    strcpy(Separators, " .,;:!?-'\"()[]{}");

    //Boucle jusqu'à ce que le user exit
    do {
        system("cls");
        print_title();
        print_status(CaseSense, Separators, SelectType, ConsecutiveWordsCount);
        print_files(files, NumberFiles);
        print_menu();

        scanf(" %d", &choice);
        set_color(COL_RESET);

        switch (choice) {

            /* ── 1. Case sensitivity ─────────────────────────────── */
            case 1:
                // Affiche l'état actuel (ON/OFF) et demande à l'utilisateur s'il veut le changer.
                set_color(COL_LABEL);
                printf("\n  Case Sensitive is currently %s.\n", CaseSense ? "ON" : "OFF");
                set_color(COL_OPTION);
                printf("  Do you want to change it ? (Y / N) : ");
                set_color(COL_VALUE);

                do {
                    scanf(" %s", CaseSensitive);

                    if ((CaseSensitive[0]=='Y'||CaseSensitive[0]=='y') && strlen(CaseSensitive)==1) {
                        /* Bascule le flag CaseSense et confirme le nouvel état */
                        CaseSense = !CaseSense;
                        msg_ok(CaseSense ? "Case Sensitive: ON" : "Case Sensitive: OFF");

                    } else if ((CaseSensitive[0]=='N'||CaseSensitive[0]=='n') && strlen(CaseSensitive)==1) {
                        /* L'utilisateur choisit de ne pas changer */
                        msg_info("Nothing changed.");

                    } else {
                        /* Saisie invalide : on redemande */
                        msg_err("Invalid input. Enter Y or N:");
                        set_color(COL_VALUE);
                    }

                } while (!(strlen(CaseSensitive)==1 && (CaseSensitive[0]=='Y'||CaseSensitive[0]=='y'|| CaseSensitive[0]=='N'||CaseSensitive[0]=='n')));

                pause_and_clear();
            break;

            /* ── 2. Separators ───────────────────────────────────── */
            case 2:
                // Affiche les séparateurs actuels et permet à l'utilisateurd'en saisir de nouveaux (toute la ligne, espaces inclus).
                set_color(COL_LABEL);
                printf("\n  Current separators : ");
                set_color(COL_VALUE);
                printf("%s\n", Separators);
                set_color(COL_OPTION);
                printf("  Enter new separators : ");
                set_color(COL_VALUE);
                scanf(" %[^\n]", Separators);
                msg_ok("Separators updated.");
                pause_and_clear();
            break;

            /* ── 3. Type selection ───────────────────────────────── */
            case 3:
                // Choisir lettres, mots, consecutive words ou phrases
                set_color(COL_HEADER);
                printf("\n  SELECT TYPE\n");
                print_separator('-', 40);
                set_color(COL_OPTION_NUM);
                printf("  1. ");
                set_color(COL_OPTION);
                printf("Letters\n");
                set_color(COL_OPTION_NUM);
                printf("  2. ");
                set_color(COL_OPTION);
                printf("Words\n");
                set_color(COL_OPTION_NUM);
                printf("  3. ");
                set_color(COL_OPTION);
                printf("Consecutive words\n");
                set_color(COL_OPTION_NUM);
                printf("  4. ");
                set_color(COL_OPTION);
                printf("Sentences\n");
                print_separator('-', 40);
                set_color(COL_HEADER);
                printf("  Choice : ");
                set_color(COL_VALUE);
                scanf("%d", &SelectType);

                while (SelectType < 1 || SelectType > 4) {
                    msg_err("Invalid! Choose between 1 and 4:");
                    set_color(COL_VALUE);
                    scanf("%d", &SelectType);
                }
                if (SelectType == 3) {
                    set_color(COL_OPTION);
                    printf("\n  How many consecutive words? : ");
                    set_color(COL_VALUE);
                    scanf("%d", &ConsecutiveWordsCount);
                    while (ConsecutiveWordsCount < 2) {
                        msg_err("Must be at least 2:");
                        set_color(COL_VALUE);
                        scanf("%d", &ConsecutiveWordsCount);
                    }
                }
                msg_ok("Type selected.");
                pause_and_clear();
            break;

            /* ── 4. Add files ────────────────────────────────────── */
            case 4:
                // Ajouter un fichier + vérification s'il a déjà été ajouté + arrete quand l'utilisateur écrit stop 
                stop = false;
                i = 1;

                set_color(COL_HEADER);
                printf("\n  ADD FILES  (type 'stop' to finish)\n");
                print_separator('-', 40);
                while (!stop) {
                    set_color(COL_OPTION);
                    printf("  File %d : ", i);
                    set_color(COL_VALUE);
                    scanf("%s", FileName);

                    if (!strcmp(FileName,"Stop") || !strcmp(FileName,"stop")) {
                        stop = true;
                    }

                    if (!stop) {
                        while (!file_existence(FileName) && strcmp(FileName,"Stop") && strcmp(FileName,"stop")) {
                            msg_err("File not found. Try again:");
                            set_color(COL_OPTION);
                            printf("  File %d : ", i);
                            set_color(COL_VALUE);
                            scanf("%s", FileName);
                        }

                        if (!strcmp(FileName,"Stop") || !strcmp(FileName,"stop")) {
                            stop = true;
                        }
                    }

                    if (!stop) {
                        while (Search(FileName,files) && strcmp(FileName,"Stop") && strcmp(FileName,"stop")) {
                            msg_err("Already added. Try another:");
                            set_color(COL_OPTION);
                            printf("  File %d : ", i);
                            set_color(COL_VALUE);
                            scanf("%s", FileName);
                        }

                        if (!strcmp(FileName,"Stop") || !strcmp(FileName,"stop")) {
                            stop = true;
                        }
                    }

                    if (!stop) {
                        files = Insert(FileName, files);
                        set_color(COL_INFO);
                        printf("  [OK]  %s added.\n", FileName);
                        set_color(COL_RESET);
                        NumberFiles++;
                        i++;
                    }
                }
                pause_and_clear();
            break;

            /* ── 5. Delete files ─────────────────────────────────── */
            case 5:
                // Meme logique que Ajouter
                if (NumberFiles == 0) {
                    msg_err("No files loaded yet.");
                    pause_and_clear();
                    break;
                }
                stop = false;
                i = 1;
                set_color(COL_HEADER);
                printf("\n  DELETE FILES  (type 'stop' to finish)\n");
                print_separator('-', 40);
                while (!stop) {
                    set_color(COL_OPTION);
                    printf("  File %d : ", i);
                    set_color(COL_VALUE);
                    scanf("%s", FileName);
                    if (!strcmp(FileName,"Stop") || !strcmp(FileName,"stop")) {
                        stop = true;
                    }
                    if (!stop) {
                        while (!Search(FileName,files) && strcmp(FileName,"Stop") && strcmp(FileName,"stop")) {
                            msg_err("Not in list. Try again:");
                            set_color(COL_OPTION);
                            printf("  File %d : ", i);
                            set_color(COL_VALUE);
                            scanf("%s", FileName);
                        }
                        if (!strcmp(FileName,"Stop") || !strcmp(FileName,"stop")) {
                            stop = true;
                        }
                    }
                    if (!stop) {
                        files = DeleteNode(FileName, files);
                        set_color(COL_WARNING);
                        printf("  [DEL] %s removed.\n", FileName);
                        set_color(COL_RESET);
                        NumberFiles--;
                        i++;
                    }
                }
                pause_and_clear();
            break;

            /* ── 6. Select paragraphs ────────────────────────────── */
            case 6:
                /* Permet à l'utilisateur de choisir quels paragraphes de
                 * chaque fichier seront inclus dans les opérations ensemblistes.
                 *
                 * Étapes :
                 *  a) On réinitialise tous les BST de paragraphes (on efface
                 *     les sélections précédentes via FreeParagraphTree).
                 *  b) Boucle de saisie : l'utilisateur entre un nom de fichier
                 *     puis le nombre de paragraphes qu'il veut sélectionner,
                 *     et enfin les numéros de paragraphes un par un.
                 *  c) Validations : fichier présent dans le BST, nombre de
                 *     paragraphes dans les limites autorisées, pas de doublon.
                 *  d) Chaque numéro validé est inséré dans le BST de paragraphes
                 *     du nœud fichier correspondant (InsertParagraph). */
                if (NumberFiles == 0) {
                    msg_err("Please add at least 1 file.");
                    pause_and_clear();
                    break;
                }
                /* Réinitialisation : efface les sélections de paragraphes
                 * de tous les fichiers avant de recommencer la sélection. */
                for (i = 1; i <= NumberFiles; i++) {
                    ptr node = Search_by_inorder(files, i);
                    FreeParagraphTree(node->paragraphs);
                    node->paragraphs = NULL;
                }

                stop = false;
                i = 1;
                set_color(COL_HEADER);
                printf("\n  AVAILABLE FILES\n");
                print_separator('-', 40);
                set_color(COL_VALUE);
                Inorder(files);
                printf("\n");
                set_color(COL_HEADER);
                printf("\n  SELECT PARAGRAPHS  (type 'stop' to finish)\n");
                print_separator('-', 40);
                while (!stop) {
                    set_color(COL_OPTION);
                    printf("  File %d : ", i);
                    set_color(COL_VALUE);
                    scanf("%s", FileName);
                    if (!strcmp(FileName,"Stop") || !strcmp(FileName,"stop")) {
                        stop = true;
                    }
                    if (!stop) {
                        /* Vérifie que le fichier saisi est dans le BST.
                         * Search retourne NULL si le fichier n'est pas trouvé. */
                        if (!Search(FileName, files)) {
                            msg_err("Not in your list.");
                            continue;
                        }
                        ptr node = Search(FileName, files);
                        int maxP = Paragraphs_number(FileName); /* Nb total de paragraphes dans ce fichier */
                        int alreadySel = CountParagraphs(node->paragraphs); /* Nb déjà sélectionnés */
                        if (alreadySel >= maxP) {
                            msg_info("All paragraphs already selected.");
                            continue;
                        }
                        set_color(COL_OPTION);
                        printf("  How many paragraphs from %s? (max %d, already %d) : ",
                               FileName, maxP - alreadySel, alreadySel);
                        set_color(COL_VALUE);
                        int nbP;
                        scanf("%d", &nbP);
                        while (nbP < 1 || nbP > maxP - alreadySel) {
                            msg_err("Invalid range:");
                            set_color(COL_VALUE);
                            scanf("%d", &nbP);
                        }
                        for (int j = 1; j <= nbP; j++) {
                            set_color(COL_OPTION);
                            printf("  Paragraph %d for %s (max %d) : ", j, FileName, maxP);
                            set_color(COL_VALUE);
                            scanf("%d", &paragraph);
                            bool alreadyChosen;
                            do {
                                /* Rejette un numéro hors limites [1..maxP] */
                                while (paragraph < 1 || paragraph > maxP) {
                                    msg_err("Out of range:");
                                    set_color(COL_VALUE);
                                    scanf("%d", &paragraph);
                                }
                                /* Rejette un paragraphe déjà sélectionné pour ce fichier */
                                alreadyChosen = (SearchParagraph(paragraph, node->paragraphs) != NULL);
                                if (alreadyChosen) {
                                    msg_err("Already chosen. Pick another:");
                                    set_color(COL_VALUE);
                                    scanf("%d", &paragraph);
                                }
                            } while (alreadyChosen);
                            /* Paragraphe valide : insertion dans le BST de paragraphes du fichier */
                            node->paragraphs = InsertParagraph(paragraph, node->paragraphs);
                            set_color(COL_INFO);
                            printf("  [OK]  Paragraph %d of %s added.\n", paragraph, FileName);
                            set_color(COL_RESET);
                        }
                        i++;
                    }
                }
                pause_and_clear();
            break;

            /* ── 7. Union ────────────────────────────────────────── */
            case 7:
                // Pour qu'elle marche minimum 1 fichier, 1 paragraphe, 1 type
                if (!validate_op(files, NumberFiles, SelectType)) { pause_and_clear(); }
                else {
                    Words result = NULL;
                    for (i = 1; i <= NumberFiles; i++) {
                        ptr fn = Search_by_inorder(files, i);
                        result = Union(fn->paragraphs, NodeValue(fn), Separators,
                                       CaseSense, result, SelectType, ConsecutiveWordsCount);
                    }
                    set_color(COL_TITLE);
                    printf("\n  UNION RESULT\n");
                    print_separator('-', 40);
                    set_color(COL_VALUE);
                    InorderWords(result);
                    printf("\n");
                    FreeWordTree(result);
                    pause_and_clear();
                }
            break;

            /* ── 8. Intersection ─────────────────────────────────── */
            case 8:
                // Pour qu'elle marche minimum 1 fichier, 1 paragraphe, 1 type
                if (!validate_op(files, NumberFiles, SelectType)) { pause_and_clear(); }
                else {
                    ParseAllParagraphs(files, NumberFiles, Separators, CaseSense, SelectType, ConsecutiveWordsCount);
                    Words result = Intersection(files, NumberFiles);
                    set_color(COL_TITLE);
                    printf("\n  INTERSECTION RESULT\n");
                    print_separator('-', 40);
                    set_color(COL_VALUE);
                    InorderWords(result);
                    printf("\n");
                    FreeWordTree(result);
                    pause_and_clear();
                }
            break;

            /* ── 9. Difference ───────────────────────────────────── */
            case 9:
                // Pour qu'elle marche minimum 1 fichier, 1 paragraphe, 1 type (en général)
                if (!validate_two_paragraphs(files, NumberFiles, SelectType)) { pause_and_clear(); }
                else {
                    ParseAllParagraphs(files, NumberFiles, Separators, CaseSense, SelectType, ConsecutiveWordsCount);

                    Words A = NULL, B = NULL;
                    if (NumberFiles == 1) {
                        ptr fn = Search_by_inorder(files, 1);
                        A = SearchParagraphByInorder(fn->paragraphs, 1)->words;
                        B = SearchParagraphByInorder(fn->paragraphs, 2)->words;
                    } else {
                        A = SearchParagraphByInorder(Search_by_inorder(files,1)->paragraphs,1)->words;
                        B = SearchParagraphByInorder(Search_by_inorder(files,2)->paragraphs,1)->words;
                    }
                    set_color(COL_TITLE);
                    printf("\n  DIFFERENCE RESULT\n");
                    print_separator('-', 40);
                    set_color(COL_LABEL);
                    printf("  A - B:\n");
                    set_color(COL_VALUE);
                    Words rAB = DifferenceAB(A, B);
                    InorderWords(rAB);
                    printf("\n");
                    FreeWordTree(rAB);
                    set_color(COL_LABEL);
                    printf("  B - A:\n");
                    set_color(COL_VALUE);
                    Words rBA = DifferenceAB(B, A);
                    InorderWords(rBA);
                    printf("\n");
                    FreeWordTree(rBA);
                    pause_and_clear();
                }
            break;

            /* ── 10. Subset ──────────────────────────────────────── */
            case 10:
                // Vérifie si A est inclus dans B et/ou B inclus A (et donc si A = B).
                // Mêmes règles que la Différence pour déterminer A et B.

                // Pour qu'elle marche minimum 1 fichier, 1 paragraphe, 1 type (en général)
                if (!validate_two_paragraphs(files, NumberFiles, SelectType)) { pause_and_clear(); }
                else {
                    ParseAllParagraphs(files, NumberFiles, Separators, CaseSense, SelectType, ConsecutiveWordsCount);

                    Words A = NULL, B = NULL;
                    if (NumberFiles == 1) {
                        /* 1 seul fichier => on compare paragraphe 1 vs paragraphe 2 */
                        ptr fn = Search_by_inorder(files, 1);
                        A = SearchParagraphByInorder(fn->paragraphs, 1)->words;
                        B = SearchParagraphByInorder(fn->paragraphs, 2)->words;
                    } else {
                        /* 2+ fichiers => on compare le premier paragraphe séléctionné de chaque fichier */
                        A = SearchParagraphByInorder(Search_by_inorder(files,1)->paragraphs,1)->words;
                        B = SearchParagraphByInorder(Search_by_inorder(files,2)->paragraphs,1)->words;
                    }

                    set_color(COL_TITLE);
                    printf("\n  SUBSET RESULT\n");
                    print_separator('-', 40);

                    set_color(COL_LABEL);
                    printf("  A ⊆ B : ");
                    set_color(COL_VALUE);
                    printf("%s\n", IsSubsetOf(A, B) ? "YES — A is a subset of B" : "NO  — A is not a subset of B");

                    set_color(COL_LABEL);
                    printf("  B ⊆ A : ");
                    set_color(COL_VALUE);
                    printf("%s\n", IsSubsetOf(B, A) ? "YES — B is a subset of A" : "NO  — B is not a subset of A");

                    // Bonus : égalité
                    if (IsSubsetOf(A, B) && IsSubsetOf(B, A)) {
                        set_color(COL_INFO);
                        printf("\n  => A and B are EQUAL sets.\n");
                    }

                    set_color(COL_RESET);
                    pause_and_clear();
                }
            break;

            /* ── 11. Complement ──────────────────────────────────── */
            case 11:
                // Pour qu'elle marche minimum 1 fichier, 1 paragraphe, 1 type
                if (!validate_op(files, NumberFiles, SelectType)) { pause_and_clear(); }
                else {
                    ParseAllParagraphs(files, NumberFiles, Separators, CaseSense, SelectType, ConsecutiveWordsCount);

                    // Construire U = union de tous les fichiers/paragraphes
                    Words U = NULL;
                    for (i = 1; i <= NumberFiles; i++) {
                        ptr fn = Search_by_inorder(files, i);
                        U = Union(fn->paragraphs, NodeValue(fn), Separators,
                                CaseSense, U, SelectType, ConsecutiveWordsCount);
                    }

                    set_color(COL_TITLE);
                    printf("\n  COMPLEMENT RESULT\n");
                    print_separator('-', 40);

                    // Pour chaque fichier, afficher U - A
                    for (i = 1; i <= NumberFiles; i++) {
                        ptr fn = Search_by_inorder(files, i);

                        // Construire A = union des paragraphes de ce fichier
                        Words A = NULL;
                        A = Union(fn->paragraphs, NodeValue(fn), Separators,
                                CaseSense, A, SelectType, ConsecutiveWordsCount);

                        set_color(COL_LABEL);
                        printf("  Complement of %s (U - A):\n", NodeValue(fn));
                        set_color(COL_VALUE);

                        Words comp = DifferenceAB(U, A);
                        if (comp == NULL)
                            printf("  (empty set)\n");
                        else
                            InorderWords(comp);
                        printf("\n");

                        FreeWordTree(comp);
                        FreeWordTree(A);
                    }

                    FreeWordTree(U);
                    set_color(COL_RESET);
                    pause_and_clear();
                }
            break;

            /* ── 12. All operations ──────────────────────────────── */
            case 12:
                // Affiche les 5 opérations
                // Pour qu'elle marche minimum 1 fichier, 1 paragraphe, 1 type (en général)
                if (!validate_two_paragraphs(files, NumberFiles, SelectType)) { pause_and_clear(); }
                else {
                    ParseAllParagraphs(files, NumberFiles, Separators, CaseSense, SelectType, ConsecutiveWordsCount);

                    // ── Préparer A et B ──────────────────────────────────────
                    Words A = NULL, B = NULL;
                    if (NumberFiles == 1) {
                        ptr fn = Search_by_inorder(files, 1);
                        A = SearchParagraphByInorder(fn->paragraphs, 1)->words;
                        B = SearchParagraphByInorder(fn->paragraphs, 2)->words;
                    } else {
                        A = SearchParagraphByInorder(Search_by_inorder(files,1)->paragraphs,1)->words;
                        B = SearchParagraphByInorder(Search_by_inorder(files,2)->paragraphs,1)->words;
                    }

                    // ── Construire U = union de tout ─────────────────────────
                    Words U = NULL;
                    for (i = 1; i <= NumberFiles; i++) {
                        ptr fn = Search_by_inorder(files, i);
                        U = Union(fn->paragraphs, NodeValue(fn), Separators, CaseSense, U, SelectType, ConsecutiveWordsCount);
                    }

                    set_color(COL_TITLE);
                    printf("\n  ALL OPERATIONS\n");
                    print_separator('=', 55);

                    // ── 1. Union ─────────────────────────────────────────────
                    set_color(COL_HEADER);
                    printf("\n  [UNION]\n");
                    print_separator('-', 40);
                    set_color(COL_VALUE);
                    InorderWords(U);
                    printf("\n");

                    // ── 2. Intersection ──────────────────────────────────────
                    set_color(COL_HEADER);
                    printf("\n  [INTERSECTION]\n");
                    print_separator('-', 40);
                    Words inter = Intersection(files, NumberFiles);
                    set_color(COL_VALUE);
                    if (inter == NULL)
                        printf("  (empty set)\n");
                    else
                        InorderWords(inter);
                    printf("\n");
                    FreeWordTree(inter);

                    // ── 3. Difference ────────────────────────────────────────
                    set_color(COL_HEADER);
                    printf("\n  [DIFFERENCE]\n");
                    print_separator('-', 40);
                    set_color(COL_LABEL);
                    printf("  A - B:\n");
                    set_color(COL_VALUE);
                    Words rAB = DifferenceAB(A, B);
                    if (rAB == NULL)
                        printf("  (empty set)\n");
                    else
                        InorderWords(rAB);
                    printf("\n");
                    FreeWordTree(rAB);

                    set_color(COL_LABEL);
                    printf("  B - A:\n");
                    set_color(COL_VALUE);
                    Words rBA = DifferenceAB(B, A);
                    if (rBA == NULL)
                        printf("  (empty set)\n");
                    else
                        InorderWords(rBA);
                    printf("\n");
                    FreeWordTree(rBA);

                    // ── 4. Subset ────────────────────────────────────────────
                    set_color(COL_HEADER);
                    printf("\n  [SUBSET]\n");
                    print_separator('-', 40);
                    set_color(COL_LABEL);
                    printf("  A ⊆ B : ");
                    set_color(COL_VALUE);
                    printf("%s\n", IsSubsetOf(A, B) ? "YES" : "NO");
                    set_color(COL_LABEL);
                    printf("  B ⊆ A : ");
                    set_color(COL_VALUE);
                    printf("%s\n", IsSubsetOf(B, A) ? "YES" : "NO");
                    if (IsSubsetOf(A, B) && IsSubsetOf(B, A)) {
                        set_color(COL_INFO);
                        printf("  => A and B are EQUAL sets.\n");
                    }

                    // ── 5. Complement ────────────────────────────────────────
                    set_color(COL_HEADER);
                    printf("\n  [COMPLEMENT]\n");
                    print_separator('-', 40);
                    for (i = 1; i <= NumberFiles; i++) {
                        ptr fn = Search_by_inorder(files, i);
                        Words Ai = NULL;
                        Ai = Union(fn->paragraphs, NodeValue(fn), Separators, CaseSense, Ai, SelectType, ConsecutiveWordsCount);
                        set_color(COL_LABEL);
                        printf("  Complement of %s:\n", NodeValue(fn));
                        set_color(COL_VALUE);
                        Words comp = DifferenceAB(U, Ai);
                        if (comp == NULL)
                            printf("  (empty set)\n");
                        else
                            InorderWords(comp);
                        printf("\n");
                        FreeWordTree(comp);
                        FreeWordTree(Ai);
                    }

                    FreeWordTree(U);
                    print_separator('=', 55);
                    set_color(COL_RESET);
                    pause_and_clear();
                }
            break;

            /* ── 13. Exit ────────────────────────────────────────── */
            case 13:
                set_color(COL_TITLE);
                printf("\n  Goodbye! Thanks for using the Text Processing Tool.\n\n");
                set_color(COL_RESET);
                pause_and_clear();
            break;

            default:
                msg_err("Invalid choice. Please choose between 1 and 13.");
                pause_and_clear();
        }
    } while (choice != 13);

    return 0;
}
