;;; cil-dark-theme.el --- A dark theme based on sanityinc-tomorrow-night -*- lexical-binding: t -*-
;; Package-Requires: ((emacs "27.1"))

;; The colors are taken from sanityinc-tomorrow-night, from the
;; color-theme-sanityinc-tomorrow package, Original source:
;; https://github.com/purcell/color-theme-sanityinc-tomorrow
;; Used with permission under the original MIT License.

  ;; '((night . ((background . "#1d1f21")
  ;;             (alt-background . "#22a224a427a7")
  ;;             (current-line . "#282a2e")
  ;;             (selection . "#373b41")
  ;;             (foreground . "#c5c8c6")
  ;;             (comment . "#969896")
  ;;             (red . "#cc6666")
  ;;             (orange . "#de935f")
  ;;             (yellow . "#f0c674")
  ;;             (green . "#b5bd68")
  ;;             (aqua . "#8abeb7")
  ;;             (blue . "#81a2be")
  ;;             (purple . "#b294bb")

  ;; test new colors:
  ;;             (dark-green . "#00994c")
  ;; ))

(deftheme cil-dark
  "A dark theme designed to use of syntax highlighning capabilities of cil-mode, based on sanityinc-tomorrow-night.")

(let ((class '((class color) (min-colors 89)))
      ;; Color palette based on sanityinc-tomorrow-night
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
      (warning "#de935f")   ; orange
      (error "#c66"))

;; (let ((class '((class color) (min-colors 89)))
;;       ;; Color palette based on sanityinc-tomorrow-night
;;       (background "#1d2526")
;;       (foreground "#c5c8c6")
;;       (cursor "#aeafad")
;;       (highlight "#2d3b44")
;;       (hl-line "#2b2b2b")
;;       (region "#3f494a")
;;       (comment "#969896")
;;       (string "#b5bd68")
;;       (keyword "#81a2be")
;;       ;; Modified faces for distinction
;;       (constant "#d08770")  ; Soft orange, distinct from type
;;       (type "#8abeb7")      ; Muted teal, clearly different from constant
;;       (function "#b294bb")
;;       (variable "#cc6666")
;;       (warning "#de935f")
;;       (error "#c66"))

  (custom-theme-set-faces
   'cil-dark
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
   'cil-dark
   `(ansi-color-names-vector [,background ,error ,string ,type ,keyword ,variable ,function ,comment])))

(when (and (boundp 'custom-theme-load-path) load-file-name)
  (add-to-list 'custom-theme-load-path
               (file-name-as-directory (file-name-directory load-file-name))))

(provide-theme 'cil-dark)
