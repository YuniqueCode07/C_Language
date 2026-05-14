# Text Processing Tool

A command-line application that performs set operations (union, intersection,
difference, subset, and complement) on words, letters, sentences, or consecutive
word groups extracted from text files.

> **Platform:** Windows only (uses WinAPI for coloured console output).

---

## Table of Contents

1. Project Structure
2. Getting Started
3. Before Running Any Operation
4. Menu Reference
5. Set Operations Explained
6. Settings Reference
7. Technical Notes & Limitations
8. Common Mistakes
9. Example Walkthrough

---

## 1. Project Structure

```
project/
├── Text_Procssing.c   ← main source file
├── Text_Procssing.h  ← header (structs, macros, prototypes)
├── README.md                    ← this file
└── File_Texts/                  ← put ALL your .txt files here
    ├── file1.txt
    ├── file2.txt
    └── ...
```

> **Important:** the program only looks for files inside the "File_Texts/"
> folder. If your file is not in that folder, the program will report that it
> does not exist, even if the filename is typed correctly.

### Text file format

- Each **paragraph** must be separated by a **blank line** (two consecutive
  newlines `\n\n`).
- A file with no blank lines is treated as a single paragraph.
- Paragraph numbers start at **1**.

**Example — `file1.txt`:**

```
The quick brown fox jumps over the lazy dog.

Rain falls softly upon the quiet street.

Sunset colors paint the sky red and gold.
```

This file contains **3 paragraphs**.

---

## 2. Getting Started

### Compile

```
gcc Text_Procssing.c -o program
```

The program requires **Windows** because it uses `SetConsoleTextAttribute`
(WinAPI) for coloured output. It will not compile or run correctly on Linux or
macOS without modification.

---

## 3. Before Running Any Operation

You **must** complete these three steps in order before using any set operation
(Union, Intersection, Difference, Subset, Complement). Skipping any of them
will show an error message and return to the menu.

```
Step 1 → Select a type          (menu option 3)
Step 2 → Add at least one file  (menu option 4)
Step 3 → Select paragraphs      (menu option 6)
```

The order matters. Always follow it.

---

## 4. Menu Reference

| Option | Name                  | Requires               | Description                                                              |
|--------|-----------------------|------------------------|--------------------------------------------------------------------------|
| 1      | Change case sensitivity | —                    | Toggle whether `Word` and `word` are treated as the same element         |
| 2      | Change separators     | —                      | Define which characters split words or letters                           |
| 3      | Select type           | —                      | Choose what to extract: letters, words, consecutive words, or sentences  |
| 4      | Add a file            | —                      | Load one or more `.txt` files from `File_Texts/`                         |
| 5      | Delete a file         | ≥ 1 file loaded        | Remove a file from the current session                                   |
| 6      | Select paragraphs     | ≥ 1 file loaded        | Choose which paragraphs to process from each file                        |
| 7      | Union                 | type + ≥ 1 paragraph   | All unique elements across all selected paragraphs                       |
| 8      | Intersection          | type + ≥ 1 paragraph   | Only elements present in every selected paragraph                        |
| 9      | Difference            | type + **exactly 2** paragraphs | Elements in A but not B, and vice versa                       |
| 10     | Subset                | type + **exactly 2** paragraphs | Check whether A ⊆ B and/or B ⊆ A                             |
| 11     | Complement            | type + ≥ 1 paragraph   | For each file, elements of the universal set U that are not in that file |
| 12     | All operations        | type + **exactly 2** paragraphs | Runs all operations (7–11) in a single pass                  |
| 13     | Exit                  | —                      | Quit the program                                                         |

> **Note on options 10, 11, and 12 — Beyond the required deliverables:**
> The lab assignment explicitly required only Union, Intersection, and
> Difference (section 4 of the subject). Subset (option 10), Complement
> (option 11), and "All operations" (option 12) were **added voluntarily**
> as extensions, even though Subset and Complement were mentioned in the
> theoretical objectives of the subject (section 2). All three are fully
> implemented and functional.

---

## 5. Set Operations Explained

All operations work on the elements extracted from the **selected paragraphs**,
according to the **selected type** and current settings (case sensitivity,
separators).

### How A and B are determined (for Difference, Subset, All operations)

These operations always compare **exactly two sets A and B**.

- **1 file loaded:** A = the 1st selected paragraph (lowest number in the BST),
  B = the 2nd selected paragraph.
- **2 or more files loaded:** A = the 1st selected paragraph of file 1,
  B = the 1st selected paragraph of file 2.

> "1st selected" means the paragraph with the lowest number among those chosen
> in option 6 — not necessarily paragraph 1 of the file.

---

### Union (option 7)

Returns every unique element that appears in **at least one** of the selected
paragraphs, across all loaded files. Duplicates are removed automatically.
Results are displayed in **alphabetical order**.

**Requires:** ≥ 1 file, ≥ 1 paragraph selected, type selected.

```
Paragraph 1 → { rain, falls, softly }
Paragraph 2 → { sun, falls, bright }

Union → { bright, falls, rain, softly, sun }
```

---

### Intersection (option 8)

Returns only elements present in **every single** selected paragraph, across
all loaded files.

- With **1 file:** the word must appear in **all** selected paragraphs of that
  file.
- With **2+ files:** the word must appear in **all** selected paragraphs of
  **every** loaded file.

**Requires:** ≥ 1 file, ≥ 1 paragraph selected, type selected.

```
Paragraph 1 → { rain, falls, softly }
Paragraph 2 → { sun, falls, bright }

Intersection → { falls }
```

---

### Difference (option 9)

Compares two sets A and B and shows what each one has that the other does not.

**Requires:** exactly **2 paragraphs** selected in total (see "How A and B are
determined" above), type selected.

```
A → { rain, falls, softly }
B → { sun, falls, bright }

A - B → { rain, softly }
B - A → { bright, sun }
```

---

### Subset (option 10)

Checks whether A ⊆ B and/or B ⊆ A. If both hold, the program reports that
A and B are **equal sets**.

**Requires:** exactly **2 paragraphs** selected in total, type selected.

```
A → { falls, rain }
B → { rain, falls, softly }

A ⊆ B → YES
B ⊆ A → NO
```

---

### Complement (option 11)

Builds the universal set **U** = union of all elements across all selected
paragraphs of all files, then displays **U − Aᵢ** for each file i.

**Requires:** ≥ 1 file, ≥ 1 paragraph selected, type selected.

---

### All operations (option 12)

Runs Union, Intersection, Difference (A−B and B−A), Subset, and Complement
in a single pass and displays all results consecutively.

**Requires:** exactly **2 paragraphs** selected in total, type selected.

---

## 6. Settings Reference

### Case sensitivity (option 1)

| State           | Effect                                           |
|-----------------|--------------------------------------------------|
| OFF *(default)* | `Rain` and `rain` are treated as the same element |
| ON              | `Rain` and `rain` are two different elements      |

Change this **before** running any operation. It takes effect on the next
parsing call.

---

### Separators (option 2)

Separators are the characters used to split the text into elements.

**Default:** ` .,;:!?-'"()[]{}` (space + common punctuation)

- For **letters:** separators are characters that are ignored (every other
  character is extracted individually).
- For **words:** separators mark the boundary between two words.
- For **sentences:** `.` `!` `?` always act as sentence-enders, regardless of
  your separator list.
- For **consecutive words:** `.` `!` `?` break the consecutive sequence — two
  words on either side of such a character are **never** considered consecutive,
  even if they are otherwise adjacent.

The separator string is limited to **49 characters** (50-byte buffer including
the null terminator).

---

### Types (option 3)

| Type | What is extracted | Example input → elements |
|------|-------------------|--------------------------|
| 1 – Letters | Every individual character that is not a separator | `"hi!"` → `{ h, i }` |
| 2 – Words | Sequences of characters between separators | `"rain falls."` → `{ rain, falls }` |
| 3 – Consecutive words | Groups of exactly N consecutive words with no sentence-break between them | `"rain falls softly"` with N=2 → `{ rain falls, falls softly }` |
| 4 – Sentences | Full text between `.` `!` `?` delimiters | `"Rain falls. Sun shines."` → `{ rain falls, sun shines }` |

For **consecutive words**, you will be asked to enter N (minimum 2). A
sentence-ending separator (`.` `!` `?`) between two words prevents them from
being grouped, even if no other separator is present.

---

### Selecting paragraphs (option 6)

- You can select paragraphs from **multiple files** in the same session.
- For each file, you choose **how many** paragraphs and then **which ones** by
  number.
- Paragraph numbers start at **1**.
- You cannot select the same paragraph twice for the same file.
- **Re-opening option 6 clears all previously selected paragraphs** and starts
  fresh — you must reselect everything.

---

## 7. Technical Notes & Limitations

### N-file support

The program supports **any number of files** simultaneously. The subject did
not specify a limit, so the implementation imposes none: files are stored in a
BST with no hardcoded maximum.

### Data structures used

The implementation uses a **three-level BST hierarchy**:

```
Files BST  (ordered alphabetically by filename)
  └── Paragraphs BST  (ordered by paragraph number, per file)
        └── Words BST  (ordered alphabetically, per paragraph)
```

An auxiliary linked-list **stack** is used for iterative in-order traversal of
the files BST. A separate linked list (`WordList`) is used internally during
type-3 parsing to build sliding windows of consecutive words.

### Buffer sizes

| Element | Maximum size |
|---------|-------------|
| Filename (as typed) | 99 characters |
| Single word or letter | 99 characters |
| Consecutive-word group (type 3) | 999 characters |
| Sentence (type 4) | 999 characters |
| Separator string | 49 characters |
| Full file path (`File_Texts/<name>`) | 511 characters |

Exceeding these sizes will cause a buffer overflow. Keep filenames, words, and
sentences within these bounds.

### Paragraph stack limit

`SearchParagraphByInorder` uses a fixed-size internal array of **100 slots**.
A file with more than 100 paragraphs could overflow this array during
traversal. In practice, ordinary text files are well within this limit.

---

## 8. Common Mistakes

| Symptom | Likely cause | Fix |
|---------|-------------|-----|
| "File doesn't exist" | File is not inside `File_Texts/` | Move the `.txt` file into that folder |
| Operation shows an error immediately | Type or paragraphs not selected | Complete steps 1 → 2 → 3 first |
| Difference / Subset / All operations show an error | Number of selected paragraphs is not exactly 2 | Select exactly 2 paragraphs total (either 2 from 1 file, or 1 from each of 2 files) |
| Union / Intersection / Complement show an error | No paragraphs selected | Select at least 1 paragraph (option 6) |
| Everything appears as one paragraph | No blank line between paragraphs in the file | Add an empty line between each paragraph in your `.txt` file |
| Re-selecting paragraphs lost previous selections | Option 6 resets all selections | This is intentional — reselect everything in one session |
| Uppercase and lowercase words counted separately | Case sensitivity is ON | Toggle it off via option 1 |
| Words split unexpectedly | Custom separator string changed | Check option 2 and restore if needed |
| Complement gives unexpected results | U is built from currently selected paragraphs only | U = union of all selected paragraphs, not the entire files |

---

## 9. Example Walkthrough

**Goal:** find words in common between paragraph 1 of `file1.txt` and
paragraph 2 of `file2.txt`.

```
1. Place file1.txt and file2.txt in File_Texts/

2. Run the program.

3. Option 3 → Select type → 2 (Words)

4. Option 4 → Add files
   File 1: file1.txt
   File 2: file2.txt
   Type: stop

5. Option 6 → Select paragraphs
   File 1: file1.txt → 1 paragraph → paragraph 1
   File 2: file2.txt → 1 paragraph → paragraph 2
   Type: stop

6. Option 8 → Intersection
   → The result shows every word present in both selected paragraphs.
```

---

*Made by AIT MESSAOUD Yanis & SEDDARI Mohamed Louay*
