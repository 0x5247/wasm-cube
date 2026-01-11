package main

import (
	"fmt"
	"net/http"
)

func main() {
	fServer := http.FileServer(http.Dir("./static"))
	http.Handle("/", disableCache(fServer))

	fmt.Println("go see http://127.0.0.1:3001")
	http.ListenAndServe(":3001", nil)
}

// disbling cache for development
func disableCache(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Cache-Control", "no-cache")
		next.ServeHTTP(w, r)
	})
}
