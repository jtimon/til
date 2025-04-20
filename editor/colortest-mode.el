;;; colortest.el --- Major mode for viewing color test files -*- lexical-binding: t -*-

(define-derived-mode colortest-mode fundamental-mode "Colortest"
  "Major mode for editing .colortest files.
Displays face names in their corresponding colors."
  (setq font-lock-defaults '((colortest-font-lock-keywords) nil t))
  (font-lock-flush))

(defconst colortest-font-lock-keywords
  (mapcar (lambda (face)
            (cons (concat "\\<" (symbol-name face) "\\>")
                  `(0 (quote ,face))))
          (face-list))
  "Font lock keywords for colortest-mode.")

;; File association
(add-to-list 'auto-mode-alist '("\\.colortest\\'" . colortest-mode))

(provide 'colortest-mode)
;;; colortest.el ends here
