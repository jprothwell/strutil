Improves C++ string support with minimal UTF-8 and string handling functions. The library is single cpp file and as easy as possible to integrate. Supports any STL-compatible string/vector types, and allows configuration of any used type. The library ships with comprehensive unit/regression test suite.

Examples:

```
trim("  a bc  ") == "a bc"
rtrim("  a bc  ") == "  a bc"
ssprintf("123=%d",123) == "123=123"
uppercase("AbCd") == "ABCD"
lowercase("AbCd") == "abcd"

vector<string> e = explode( ",", "jani,markus,kajala" )
e.size() == 3
e[0] == "jani"
e[1] == "markus"
e[2] == "kajala"
implode(",",e) == "jani,markus,kajala"

substr("abcd",1,2) == "bc"
substr("abcd",1,3) == "bcd"
substr("abcd",0,4) == "abcd"
substr("abcd",-1) == "d"
substr("abcd",0,-1) == "abc"
substr("abcd",0,-2) == "ab"
substr("myfile.dat",0,-4) == "myfile"
substr("myfile.dat",-4) == ".dat"

replace("\\","/","C:\\dos\\path\\") == "C:/dos/path/"
replace('\\','/',"C:\\dos\\path\\") == "C:/dos/path/"

basename("a/b/test.tmp") == "test.tmp"
basename("a/b/test.tmp/") == "test.tmp"
basename("a/b/test.tmp/ ") == " "
basename("C:\\a\\b\\test.tmp") == std::string("test.tmp")

dirname("") == ""
dirname("/") == "/"
dirname(" ") == "."
dirname("asdasd") == "."
dirname("asdasd/") == "."
dirname("/asdasd") == "/"
dirname("/asd/adas") == "/asd"
dirname("/asda/asd/") == "/asda"
```