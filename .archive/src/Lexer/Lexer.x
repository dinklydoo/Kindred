{
  module Main(main) where
}

%wrapper "basic"

$digit = 0-9
$alpha = [a-zA-Z]

tokens :-
  $white+                        ;
  "@*".*                         { \s -> Com_S }
  *."*@"                         { \s -> Com_E }
  "@".*                          ;
  "bool"                         { \s -> T_Bool }
  "char"                         { \s -> T_Char }
  "int"                          { \s -> T_Int }
  "long"                         { \s -> T_Long }
  "float"                        { \s -> T_Float }
  "double"                       { \s -> T_Double }
  "case"                         { \s -> Case }
  "lamb"                         { \s -> Lamb }
  "func"                         { \s -> Func }
  $digit+                        { \s -> Int (read s) }
  [\=\+\-\*\/\(\)\:]             { \s -> Sym (head s) }
  $alpha [$alpha $digit \_ \']*  { \s -> Var s }

{

data Token
  = Com_S -- comment start
  | Com_E -- comment end
  | Int Integer -- literal values (will be type specified into Int/Long in parsing)
  | Float Double -- literal values (same as int but with double/float)
  | T_Int -- numeric typings
  | T_Long
  | T_Float
  | T_Double
  | T_Bool -- boolean typing
  | T_Char -- char typing
  | Case -- case
  | Lamb -- lambda expression
  | Func -- function
  | Label String -- function variable labels



  deriving (Eq,Show)

-- need to accept arbitrary tokens for multiline comments
-- when we encounter a (Com_S,Com_E) we cant throw lex errors due to comments

main = do
  s <- getContents
  print(alexScanTokens s)
}