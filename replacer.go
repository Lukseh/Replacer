package main

/*
	#cgo CFLAGS: -I.
  #cgo LDFLAGS: -L. -lreplacer
	#include "./replacer.h"
*/
import "C"
import "fmt"

type Reps struct {
	Pattern string
	Value   string
}

// char *Replace(const char *source, const char *pattern, const char *value);
func Replace(source string, pattern string, value string) string {
	return C.GoString(C.Replace(C.CString(source), C.CString(pattern), C.CString(value)))
}

// char *ReplaceVWrapper(const char *source, const char *pattern, const char *value);
func (self *Reps) Replace(source string) string {
	return C.GoString(C.ReplaceVWrapper(C.CString(source), C.CString(self.Pattern), C.CString(self.Value)))
}

// char *ReplaceAll(const char *source, Reps *reps, size_t amount);
func ReplaceAll(source string, reps []Reps) string {
	cReps := make([]C.Reps, len(reps))
	for i, r := range reps {
		cReps[i].pattern = C.CString(r.Pattern)
		cReps[i].value = C.CString(r.Value)
	}
	return C.GoString(C.ReplaceAll(C.CString(source), &cReps[0], C.size_t(len(reps))))
}

func main() {
	src := "I like $ITEM;, $ITEM and $BRR;. $BRR is american band."
	IceCream := Reps{
		Pattern: "ITEM",
		Value:   "Ice cream",
	}
	var reps []Reps
	reps = append(reps, IceCream)
	reps = append(reps, Reps{
		Pattern: "BRR",
		Value:   "Deftones",
	})
	fmt.Printf("Replace(\"%s\") with effect: \"%s\"\n", src, Replace(src, "ITEM", "Ice cream"))
	fmt.Printf("ReplaceV(\"%s\") with effect: \"%s\"\n", src, IceCream.Replace(src))
	fmt.Printf("ReplaceAll(\"%s\") with effect: \"%s\"\n", src, ReplaceAll(src, reps))
}
