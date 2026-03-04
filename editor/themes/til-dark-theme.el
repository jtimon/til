;;; til-dark-theme.el --- A dark theme based on sanityinc-tomorrow-night -*- lexical-binding: t -*-

;; The colors are initially taken from sanityinc-tomorrow-night, from the
;; color-theme-sanityinc-tomorrow package, Original source:
;; https://github.com/purcell/color-theme-sanityinc-tomorrow
;; Used with permission under the original MIT License.

(deftheme til-dark
  "A dark theme designed to use all syntax highlighting capabilities of til-mode, based initially on sanityinc-tomorrow-night.")

(let ((class '((class color) (min-colors 89)))
      ;; Color palette initially based on sanityinc-tomorrow-night
      (background "#1d1f21")
      (foreground "#c5c8c6")
      (cursor "#aeafad")
      (highlight "#2d3b44")
      (hl-line "#2b2b2b")
      (region "#3f494a")
      (comment "#969896")
      (string "#8abeb7")    ; aqua
      (keyword "#b5bd68")   ; green
      (constant "#f0c674")  ; yellow
      (type "#81a2be")      ; blue
      (function "#00994c")  ; dark-green instead of purple b294bb
      (variable "#d08770")  ; Soft orange
      (builtin "#b0c4de")   ; LightSteelBlue
      (preprocessor "#b294bb") ; Muted magenta
      (warning "#de935f")   ; orange
      (error "#c66"))

  ;; Soft red-orange like #e78c45

  (custom-theme-set-faces
   'til-dark
   `(default ((,class (:background ,background :foreground ,foreground))))
   `(cursor ((,class (:background ,cursor))))
   `(highlight ((,class (:background ,highlight))))
   `(hl-line ((,class (:background ,hl-line))))
   `(region ((,class (:background ,region))))
   `(font-lock-comment-face ((,class (:foreground ,comment))))
   `(font-lock-comment-delimiter-face ((,class (:foreground ,comment))))
   `(font-lock-string-face ((,class (:foreground ,string))))
   `(font-lock-keyword-face ((,class (:foreground ,keyword))))
   `(font-lock-constant-face ((,class (:foreground ,constant))))  ; Changed to orange
   `(font-lock-type-face ((,class (:foreground ,type))))         ; Changed to teal
   `(font-lock-function-name-face ((,class (:foreground ,function))))
   `(font-lock-variable-name-face ((,class (:foreground ,variable))))
   `(font-lock-builtin-face ((,class (:foreground ,builtin))))
   `(font-lock-preprocessor-face ((,class (:foreground ,preprocessor))))
   `(font-lock-warning-face ((,class (:foreground ,warning))))
   `(error ((,class (:foreground ,error))))
   `(fringe ((,class (:background ,background :foreground ,foreground))))
   `(vertical-border ((,class (:foreground ,comment))))
   `(minibuffer-prompt ((,class (:foreground ,keyword))))
   `(mode-line ((,class (:background ,highlight :foreground ,foreground))))
   `(mode-line-inactive ((,class (:background ,background :foreground ,comment))))
   `(link ((,class (:foreground ,keyword :underline t))))
   `(link-visited ((,class (:foreground ,function :underline t))))
   `(button ((,class (:foreground ,keyword :underline t))))
   `(header-line ((,class (:background ,highlight :foreground ,foreground))))
   `(show-paren-match ((,class (:background ,highlight :foreground ,keyword))))
   `(show-paren-mismatch ((,class (:background ,error :foreground ,foreground))))
   `(isearch ((,class (:background ,keyword :foreground ,background))))
   `(lazy-highlight ((,class (:background ,function :foreground ,background))))
   `(trailing-whitespace ((,class (:background ,warning))))
   `(escape-glyph ((,class (:foreground ,constant))))
   `(nobreak-space ((,class (:foreground ,constant))))
   `(compilation-error ((,class (:foreground ,error))))
   `(compilation-warning ((,class (:foreground ,warning))))
   `(compilation-info ((,class (:foreground ,type))))
   `(dired-directory ((,class (:foreground ,keyword))))
   `(dired-ignored ((,class (:foreground ,comment))))
   `(dired-mark ((,class (:foreground ,function))))
   `(dired-symlink ((,class (:foreground ,type)))))

  (custom-theme-set-variables
   'til-dark
   `(ansi-color-names-vector [,background ,error ,string ,type ,keyword ,variable ,function ,comment])))

(when (and (boundp 'custom-theme-load-path) load-file-name)
  (add-to-list 'custom-theme-load-path
               (file-name-as-directory (file-name-directory load-file-name))))

(provide-theme 'til-dark)
