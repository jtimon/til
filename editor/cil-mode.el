;;; cil-mode.el --- Major mode for editing cil files
;; A basic major mode for the cil language, developed at https://github.com/jtimon/cil.

(defconst cil-mode-syntax-table
  (with-syntax-table (copy-syntax-table)
    ;; Comments: // and #
    (modify-syntax-entry ?/ ". 124b")
    (modify-syntax-entry ?# "< b")
    (modify-syntax-entry ?\n "> b")
    ;; Strings
    (modify-syntax-entry ?\" "\"")
    ;; Punctuation
    (modify-syntax-entry ?: ".")
    (modify-syntax-entry ?= ".")
    (modify-syntax-entry ?( "()")
    (modify-syntax-entry ?) ")(")
    (modify-syntax-entry ?{ "(}")
    (modify-syntax-entry ?} "){")
    (modify-syntax-entry ?, ".")
    (syntax-table))
  "Syntax table for `cil-mode'.")

(defconst cil-keywords
  '("mode" "mut" "struct" "enum" "func" "proc"
    "ext_func" "ext_proc" "macro" "return" "returns" "throw" "throws"
    "if" "else" "while" "switch" "case" "true" "false"))

(defconst cil-types
  '("I64" "Bool" "String"))

(defconst cil-builtins
  '("and" "or" "not" "eq" "str_eq" "concat" "str_len"
    "str_get_substr" "lt" "lteq" "gt" "gteq" "add" "sub"
    "mul" "div" "atoi" "itoa" "eval_to_str" "exit" "import"
    "input_read_line" "print" "println" "readfile" "runfile"))

(defconst cil-error-words
  '("static" "var" "const" "global" "fn" "function" "try" "catch")
  "Words that are invalid in cil and should be highlighted as errors.")

(defconst cil-highlights
  `(;; Error words
    (,(regexp-opt cil-error-words 'symbols) . compilation-error)
    ;; Keywords
    (,(regexp-opt cil-keywords 'symbols) . font-lock-keyword-face)
    ;; Built-in Types
    (,(regexp-opt cil-types 'symbols) . font-lock-type-face)
    ;; Builtins
    (,(regexp-opt cil-builtins 'symbols) . font-lock-builtin-face)
    ;; Type declarations: 'enum' and 'struct'
    ("\\<\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*:=\\s-*\\(enum\\|struct\\)" 1 font-lock-type-face)
    ;; Assignments (mutable variables)
    ("\\<\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*=\\s-*[^:=]" 1 font-lock-variable-name-face)
    ;; Types in declarations, signatures, and enum variants
    ("\\<\\(mut\\s-+\\|case\\s-+\\)?\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*:\\s-*\\([a-zA-Z_][a-zA-Z0-9_]*\\)" 3 font-lock-type-face)
    ("\\<returns\\s-+\\([a-zA-Z_][a-zA-Z0-9_]*\\)" 1 font-lock-type-face)
    ;; Function and procedure names
    ("\\<\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*:=\\s-*\\(func\\|proc\\|macro\\|ext_func\\|ext_proc\\)" 1 font-lock-function-name-face)
    ;; Mutable variables and arguments (anything after 'mut')
    ("\\<mut\\s-+\\([a-zA-Z_][a-zA-Z0-9_]*\\)" 1 font-lock-variable-name-face)
    ;; Constant arguments (no 'mut', in function signatures)
    ("\\<\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*:\\s-*[a-zA-Z_][a-zA-Z0-9_]*\\s-*[,)]" 1 font-lock-constant-face)
    ;; Inferred constants (no 'mut', with ':=')
    ("\\<\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*:=\\s-*" 1 font-lock-constant-face)
    ;; WIP Inferred constants (no 'mut', with ': =', ie with spaces inbetween the ':' and the '=')
    ;; ("\\<\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*: *\\s*=\\s-*" 1 font-lock-constant-face)
    ;; ("\\<\\(?!mut\\s-+\\)\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*:\\s*=\\s-*[0-9]+\\|\"[^\"]*\"\\|'[^']*'\\|true\\|false" 1 font-lock-constant-face)
    ;; WIP Non inferred constants (no 'mut', with : type '=')
    ;; ("\\<\\(?!mut\\s-+\\)\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*:\\s-*[a-zA-Z_][a-zA-Z0-9_]*\\s-*=\\s-*[0-9]+\\|\"[^\"]*\"\\|'[^']*'\\|true\\|false" 1 font-lock-constant-face)
    ;; TODO Enum values as constants
))

(defun cil-indent-line ()
  "Indent current line as cil code."
  (interactive)
  (let ((indent-col 0))
    (save-excursion
      (beginning-of-line)
      (let ((case-fold-search nil)) ; Enable case sensitivity
        (cond
         ((looking-at-p "[ \t]*}")
          (condition-case nil
              (progn
                (backward-up-list 1)
                (setq indent-col (current-indentation)))
            (error (setq indent-col 0))))
         ((looking-at-p "[ \t]*case\\b")
          (condition-case nil
              (progn
                (backward-up-list 1)
                (re-search-backward "switch\\b" nil t)
                (setq indent-col (current-indentation)))
            (error (setq indent-col 0))))
         (t
          (condition-case nil
              (while t
                (backward-up-list 1)
                (when (looking-at "{")
                  (setq indent-col (+ indent-col 4))))
              (error nil))))))
    (indent-line-to indent-col)
    ;; Ensure that the line is indented with spaces
    (when (and (not (zerop indent-col)) (not (looking-at-p "[ \t]*$")))
      (let ((spaces (make-string 4 ?\s))) ; Create a string of 4 spaces
        (delete-region (line-beginning-position) (point))
        (insert spaces)))))

(define-derived-mode cil-mode prog-mode "cil"
  "Major Mode for editing cil source code."
  :syntax-table cil-mode-syntax-table
  (setq font-lock-defaults '(cil-highlights))
  (setq indent-line-function 'cil-indent-line)
  (setq-local indent-tabs-mode nil)          ; Use spaces, not tabs
  (setq-local tab-width 4)                   ; Set tab width to 4 spaces
  (setq-local comment-start "// ")           ; Default comment prefix for region commenting
  (setq-local comment-start-skip "//+\\s-*") ; Only recognize // for highlighting and commenting
  (setq-local comment-end "")                ; Single-line comments, no end delimiter
  (setq-local comment-multi-line nil))       ; Enforce single-line comment style

(add-to-list 'auto-mode-alist '("\\.cil\\'" . cil-mode))

(provide 'cil-mode)
