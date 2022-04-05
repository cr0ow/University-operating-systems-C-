# Fork - exec

![task](ex2.png)

## Ile procesow powstanie przy n-krotnym wywolaniu funkcji `fork-exec` jak wyzej i dlaczego?
Powstanie n procesów (nie licząc procesu macierzystego), ponieważ funkcja
`fork` została wykonana n razy, natomiast funkcja `exec` nie tworzy dodatkowych
procesów potomnych.