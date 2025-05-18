;;; cil-mode.el --- Major mode for editing cil files
;; A basic major mode for the cil language, developed at https://github.com/jtimon/cil.

(defconst cil-mode-syntax-table
  (with-syntax-table (copy-syntax-table)
    ;; Line comments: // and #
    (modify-syntax-entry ?/ ". 124b")
    (modify-syntax-entry ?* ". 23")
    (modify-syntax-entry ?# "< b")
    (modify-syntax-entry ?\n "> b")
    ;; Strings
    (modify-syntax-entry ?\" "\"")
    ;; Punctuation
    (modify-syntax-entry ?: ".")
    (modify-syntax-entry ?= ".")
    (modify-syntax-entry ?\( "()")
    (modify-syntax-entry ?\) ")(")
    (modify-syntax-entry ?{ "(}")
    (modify-syntax-entry ?} "){")
    (modify-syntax-entry ?, ".")
    (syntax-table))
  "Syntax table for `cil-mode'.")

(defconst cil-keywords
  '("mode" "mut" "struct" "enum" "main"
    "func" "proc" "ext_func" "ext_proc" "macro"
    "returns" "return" "throws"
    "if" "else" "while" "switch" "case" "true" "false"
    ))

(defconst cil-types
  '("U8" "I64" "Bool" "Str"))

(defconst cil-builtins
  '("and" "or" "not" "eq" "branchless"
    "lt" "lteq" "gt" "gteq"
    "add" "sub" "mul" "div" "mod"
    "concat" "fmt" "to_str" "to_i64" "to_u8"
    "len" "size_of"
    "malloc" "memcpy" "memset" "free"
    "print" "println" "readfile" "runfile" "exit" "import" "loc"
    "assert" "assertm" "assert_eq" "assert_eq_str"
    "input_read_line" "eval_to_str"
    "lib" "pure" "script" "safe_script" "cli" "test"
    ))

(defconst cil-error-words
  '("throw" "catch" "panic" "exit" "TODO" "NULL"
    "static" "let" "var" "const" "global" "fn" "function" "try"
    )
  "Words that are invalid in cil and should be highlighted as errors.")

(defconst comment-error-words
  '("TODO" "FIX" "FIXME" "WIP")
  "Words to highlight as errors in comments.")

;; TODO FIX warnings in comments
(defconst comment-warning-words
  '("REM" "WARNING")
  "Words to highlight as warning in comments.")

(defconst cil-highlights `(
    ;; Doc comments /** ... */
    ("/\\*\\*\\([^*]\\|\\*[^/]\\)*\\*/" . font-lock-doc-face)
    ;; Error words
    (,(regexp-opt cil-error-words 'symbols) . compilation-error)
    ;; Error words in comments
    (,(concat comment-start-skip "\\(.*\\<\\(" (regexp-opt comment-error-words t) "\\)\\>\\)") . (2 compilation-error t))
    ;; Warning words in comments
    (,(concat comment-start-skip "\\(.*\\<\\(" (regexp-opt comment-warning-words t) "\\)\\>\\)") . (2 font-lock-warning-face t))
    ;; Keywords
    (,(regexp-opt cil-keywords 'symbols) . font-lock-keyword-face)
    ;; Built-in Types
    (,(regexp-opt cil-types 'symbols) . font-lock-type-face)
    ;; Builtins
    (,(regexp-opt cil-builtins 'symbols) . font-lock-builtin-face)
    ;; Numeric literals (not part of identifiers)
    ("\\(?:^\\|[^a-zA-Z0-9_]\\)\\([0-9]+\\(?:\\.[0-9]+\\)?\\)\\_>" 1 font-lock-preprocessor-face)
    ;; Type declarations: 'enum' and 'struct'
    ("\\<\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*:=\\s-*\\(enum\\|struct\\)" 1 font-lock-type-face)
    ;; Assignments (mutable variables)
    ("\\<\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*=\\s-*[^:=]" 1 font-lock-variable-name-face)
    ;; Types in declarations, signatures, and enum variants
    ("\\<\\(mut\\s-+\\|case\\s-+\\)?\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*:\\s-*\\([a-zA-Z_][a-zA-Z0-9_]*\\)" 3 font-lock-type-face)
    ("\\<returns\\s-+\\([a-zA-Z_][a-zA-Z0-9_]*\\)" 1 font-lock-type-face)
    ;; Enum variants without types
    ("\\<\\([a-zA-Z_][a-zA-Z0-9_]*\\)\\s-*[,}]" 1 font-lock-constant-face)
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
  "Indent current line as cil code using 4 spaces."
  (interactive)
  (let ((indent 0)
        (not-indented t))
    (save-excursion
      (beginning-of-line)
      (skip-chars-forward " \t")
      (cond
       ;; Closing brace: align with opening block
       ((looking-at "[ \t]*}")
        (condition-case nil
            (progn
              (backward-up-list 1)
              (setq indent (current-indentation))
              (setq not-indented nil))
          (error (setq indent 0))))
       ;; Closing parenthesis: align with line containing opening parenthesis
       ((looking-at "[ \t]*)")
        (condition-case nil
            (progn
              (backward-up-list 1)
              (save-excursion
                (beginning-of-line)
                (setq indent (current-indentation)))
              (setq not-indented nil))
          (error (setq indent 0))))
       ;; Case statements: align with parent switch (case-sensitive)
       ((let ((case-fold-search nil)) (looking-at "\\<case\\>"))
        (condition-case nil
            (progn
              (backward-up-list 1)
              (when (looking-at "{")
                (goto-char (match-beginning 0))
                (backward-sexp 1)
                (if (looking-at "\\<switch\\>")
                    (progn
                      (message "Indent case at %d (switch)" (current-indentation))
                      (setq indent (current-indentation)))
                  (message "Indent case at %d (no switch)" (current-indentation))
                  (setq indent (current-indentation))))
              (setq not-indented nil))
          (error
           (message "Error in case indentation")
           (setq indent 0))))
       ;; Other lines: indent based on open blocks or parentheses
       (t
        (condition-case nil
            (while not-indented
              (backward-up-list 1)
              (cond
               ;; Inside a block: indent 4 spaces from block's indentation
               ((looking-at "{")
                (message "Indent block at %d" (+ (current-indentation) 4))
                (setq indent (+ (current-indentation) 4))
                (setq not-indented nil))
               ;; Inside parentheses: indent 4 spaces from line's indentation
               ((looking-at "(")
                (save-excursion
                  (beginning-of-line)
                  (message "Indent paren at %d" (+ (current-indentation) 4))
                  (setq indent (+ (current-indentation) 4)))
                (setq not-indented nil))))
          (error
           (message "Error in default indentation")
           (setq indent 0))))))
    ;; Apply indentation
    (beginning-of-line)
    (delete-horizontal-space)
    (indent-to indent)))

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
  (setq-local comment-multi-line nil)        ; Enforce single-line comment style
  ;; Enable nested multi-line comments
  ;; NOTE: While CIL supports nested /* ... */ comments,
  ;; Emacs syntax highlighting does not. This mode will only highlight up to the first '*/' matching.
  (setq-local font-lock-syntactic-face-function
	      (lambda (state)
		(cond
		 ((nth 4 state)
		  (save-excursion
		    (goto-char (nth 8 state))
		    (if (looking-at "/\\*\\*")
			'font-lock-doc-face
		      'font-lock-comment-face)))
		 ((nth 3 state)
		  'font-lock-string-face)
		 (t nil))))
  )

(add-to-list 'auto-mode-alist '("\\.cil\\'" . cil-mode))

(provide 'cil-mode)
