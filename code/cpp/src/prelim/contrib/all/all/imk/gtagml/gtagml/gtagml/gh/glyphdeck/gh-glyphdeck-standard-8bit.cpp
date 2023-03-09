

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "gh-glyphdeck-standard-8bit.h"

#include <QVector>

GH_Glyphdeck_Standard_8bit::GH_Glyphdeck_Standard_8bit()
{

}

/*

64 accents or - 16?
#ifdef HIDE
0: null
1: _ empty
2: ` // acute
3: ' // grave
4: ^ // circ
5: " // uml
6: ~ // tilde
7: = // macr
8: . // dot
9: u // breve
10: v // caron
11: H // dbl acute   (xml = dblac)
12: b // bar-under    // no xml
13: c // cedil       
14: k // ogon
15: r // ring over ...    (xml = ring)
16: R // ring over (alt), e.g. aa instead of ra ...   (xml = ring)
17: K // stroke      (xml = strok)
18: t // tie-after   // no xml
19: / // slash
20: m // midot
 ... no xml ...
21: g // eng, kgreen, geminated l, ital &  ...
22: G // eng, ital, geminated L, & with more space

23: h // eth, thorn, Thorn 
24: z // eszat i.e. ss ...

25: e // ae, oe
26: E // AE, OE

27: f // fi, fj, fl, ff, FI, FJ, FL, FF 

28: F // fi, ffj, ffl, FFI, FFJ, FFL

29: n // no ligature
30: N // no ligature
31: C // italic correction

32: @ // special circled
33: ) // circled
34: % // circle left
35: o // circle ring
36: O // circle ring (larger)

37: $ // strike
38: - // strike

39: D // dieresis

?40: [
?41: ]
?42: {
?43: }
?44: ,
?45: ;

46: : // elevated

// // multi-character codes: 
 //    + double elevated
 //    > double 
 //    & triple
 //    \ external 
 //   e.g.
 //     |:t (TM as one character)   
 //     |+t (TM as two characters) 
 //     |fl (fl ligature as one character)
 //     |Fl (ffl ligature as one character)
 //     |>fl (fl ligature as two character)
 //     |&Fl (ffl ligature as three characters) 

47: < // inherited
48: + // middle inherited
49: > // double inherited


??
50: 0
51: 1
52: 2
53: 3
54: 4
55: 5
56: 6
57: 7
58: 8
59: 9

60: # // special 
61: * // special 

62: V // (invert)

63: ? // unrec


 static QMap<u1, QString> static_map {

   { 10118, "&inodot;" },  //  _.i
   { 10119, "&inodot;" },  //  _.j

   { 12123, "&eng;" },  //  g.n
   { 12150, "&ENG;" },  //  g.N

   { 12110, "&amp;" },  //  g.a //? &#128629;
   { 12120, "&kgreen;" },  //  g.k
   { 12137, "&amp;" },  //  g.A //? &#128629;
   { 12147, "&kgreen;" },  //  g.K  
  
   { 12223, "&eng;" },  //  G.n  
   { 12250, "&ENG;" },  //  G.N 
 
   { 12210, "&amp;" },  //  G.a ? &#128629;
   { 12220, "&kgreen;" },  //  G.k
   { 12237, "&amp;" },  //  G.A ? &#128629;
   { 12247, "&kgreen;" },  //  G.K  

   { 11610, "&Aring;" },  //  R.a  
   { 11637, "&aring;" },  //  R.A  

   { 14610, "&ordf;" }, // :.a
   { 24610, "&ordf;" }, // :.a
   { 14637, "&ordf;" }, // :.A
   { 24637, "&ordf;" }, // :.A

   { 14624, "&ordm;" }, // :.o
   { 24624, "&ordm;" }, // :.o
   { 14651, "&ordm;" }, // :.O
   { 24651, "&ordm;" }, // :.O

   { 14629, "&trade;" }, // :.t
   { 24629, "&trade;" }, // :.t

   { 14631, "&#8480;" }, // :.v
   { 24631, "&#8480;" }, // :.v

   { 14628, "st" }, // :.s  i.e. 1st ...
   { 24628, "st" }, // :.s
   { 14655, "st" }, // :.S  
   { 24655, "st" }, // :.S

   { 14623, "nd" }, // :.n  i.e. 2nd ...
   { 24623, "n" }, // :.n
   { 14650, "nd" }, // :.N  
   { 24650, "n" }, // :.N

   { 14627, "rd" }, // :.r  i.e. 3rd ...
   { 24627, "rd" }, // :.r
   { 14654, "rd" }, // :.R  
   { 24654, "rd" }, // :.R

   { 14617, "th" }, // :.h  i.e. 4th ...
   { 24617, "th" }, // :.h
   { 14644, "th" }, // :.H  
   { 24644, "th" }, // :.H

   { 12310, "&eth;" },  //  h.d  
   { 12337, "&ETH;" },  //  h.D  
   { 12329, "&thorn;" },  //  h.t  
   { 12156, "&THORN;" },  //  h.T

   { 12428, "&szlig;" },  //  z.s  
   { 12455, "&szlig;" },  //  z.S  

   { 12510, "&aelig;" },  //  e.a  
   { 12524, "&oelig;" },  //  e.o  
   { 12537, "&AElig;" },  //  e.A
   { 12551, "&OElig;" },  //  e.O
  
   { 12610, "&aelig;" },  //  E.a  
   { 12624, "&oelig;" },  //  E.o  
   { 12637, "&AElig;" },  //  E.A  
   { 12651, "&OElig;" },  //  E.O 

   { 13212, "&copy;" }, // @.c
   { 13227, "&reg;" }, // @.r

   { 13412, "[&copy;]" }, // %.c

   { 13936, "&diaresis;"}, // D._


tex ...

   { 10323, "{\\dianapos}" }, // '.n
   { 10350, "{\\diaNapos}" }, // '.N

   { 20323, "{\\ddianapos" }, // '.n
   { 20350, "{\\ddiaNapos" }, // '.N
 
   { 12119, "{\\diaij}" },  //  g.j
   { 12146, "{\\diaIJ}" },  //  g.J

   { 22118, "{\\ddiaij" },  //  g.i
   { 22145, "{\\ddiaIJ" },  //  g.I

   { 12123, "{\\ng}" },  //  g.n
   { 12150, "{\\NG}" },  //  g.N

   { 12110, "{\\&}" },  //  g.a
   { 12120, "\\textsc{k}" },  //  g.k
   { 12137, "{\\upamp}" },  //  g.A
   { 12147, "{\\Kgreenalt}" },  //  g.K  
  
   { 12223, "{\\ngalt}" },  //  G.n  
   { 12250, "{\\NGalt}" },  //  G.N 
 
   { 12210, "{\\itampalt}" },  //  G.a  
   { 12220, "{\\kGreenalt}" },  //  G.k
   { 12237, "{\\upampalt}" },  //  G.A
   { 12247, "{\\Kgreenalt}" },  //  G.K  

   { 11610, "{\\aa}" },  //  R.a  
   { 11637, "{\\AA}" },  //  R.a  

   { 12310, "{\\dh}" },  //  h.d  
   { 12337, "{\\DH}" },  //  h.D  
   { 12329, "{\\th}" },  //  h.t  
   { 12156, "{\\TH}" },  //  h.T

   { 12428, "{\\ss}" },  //  z.s  
   { 12455, "{\\sSalt}" },  //  z.S  

   { 12510, "{\\ae}" },  //  e.a  
   { 12524, "{\\oe}" },  //  e.o  
   { 12537, "{\\Aealt}" },  //  e.A
   { 12551, "{\\Oealt}" },  //  e.O
  
   { 12610, "{\\aEalt}" },  //  E.a  
   { 12624, "{\\oEalt}" },  //  E.o  
   { 12637, "{\\AE}" },  //  E.A  
   { 12651, "{\\OE}" },  //  E.O 

   { 13136, "{\\/}" }, // C._

   { 13212, "{\\textcopyright}" }, // @.c
   { 13227, "{\\textregistered}" }, // @.r

   { 13412, "{\\textcopyleft}" }, // %.c

   { 13936, "{\\\"}"}, // D._

   { 14610, "{\\diaordfem}" }, // :.a
   { 24610, "{\\ddiaordfem}" }, // :.a
   { 14637, "{\\diaordfemalt}" }, // :.A
   { 24637, "{\\ddiaordfemalt}" }, // :.A

   { 14624, "{\\diaordmasc}" }, // :.o
   { 24624, "{\\ddiaordmasc}" }, // :.o
   { 14651, "{\\diaordmascalt}" }, // :.O
   { 24651, "{\\ddiaordmascalt}" }, // :.O

   { 14629, "{\\texttrademark}" }, // :.t
   { 24629, "{\\ttrademark" }, // :.t

   { 14631, "{\\textservicemark}" }, // :.v
   { 24631, "{\\tservicemark" }, // :.v

   { 14628, "{\\diaST}" }, // :.s  i.e. 1st ...
   { 24628, "{\\ddiaST}" }, // :.s
   { 14655, "{\\altdiaST}" }, // :.S  
   { 24655, "{\\altddiaST" }, // :.S

   { 14623, "{\\diaND}" }, // :.n  i.e. 2nd ...
   { 24623, "{\\ddiaND}" }, // :.n
   { 14650, "{\\altdiaND}" }, // :.N  
   { 24650, "{\\altddiaND" }, // :.N

   { 14627, "{\\diaRD}" }, // :.r  i.e. 3rd ...
   { 24627, "{\\ddiaRD}" }, // :.r
   { 14654, "{\\altdiaRD}" }, // :.R  
   { 24654, "{\\altddiaRD" }, // :.R

   { 14617, "{\\diaTH}" }, // :.h  i.e. 4th ...
   { 24617, "{\\ddiaTH}" }, // :.h
   { 14644, "{\\altdiaTH}" }, // :.H  
   { 24644, "{\\altddiaTH" }, // :.H



#endif





 case 0: return '0';
 case 1: return '1';
 case 2: return '2';
 case 3: return '3';
 case 4: return '4';
 case 5: return '5';
 case 6: return '6';
 case 7: return '7';
 case 8: return '8';
 case 9: return '9';
 case 10: return 'a';
 case 11: return 'b';
 case 12: return 'c';
 case 13: return 'd';
 case 14: return 'e';
 case 15: return 'f';
 case 16: return 'g';
 case 17: return 'h';
 case 18: return 'i';
 case 19: return 'j';
 case 20: return 'k';
 case 21: return 'l';
 case 22: return 'm';
 case 23: return 'n';
 case 24: return 'o';
 case 25: return 'p';
 case 26: return 'q';
 case 27: return 'r';
 case 28: return 's';
 case 29: return 't';
 case 30: return 'u';
 case 31: return 'v';
 case 32: return 'w';
 case 33: return 'x';
 case 34: return 'y';
 case 35: return 'z';
 case 36: return '_';
 case 37: return 'A';
 case 38: return 'B';
 case 39: return 'C';
 case 40: return 'D';
 case 41: return 'E';
 case 42: return 'F';
 case 43: return 'G';
 case 44: return 'H';
 case 45: return 'I';
 case 46: return 'J';
 case 47: return 'K';
 case 48: return 'L';
 case 49: return 'M';
 case 50: return 'N';
 case 51: return 'O';
 case 52: return 'P';
 case 53: return 'Q';
 case 54: return 'R';
 case 55: return 'S';
 case 56: return 'T';
 case 57: return 'U';
 case 58: return 'V';
 case 59: return 'W';
 case 60: return 'X';
 case 61: return 'Y';
 case 62: return 'Z';
 case 63: return ' ';

 //  64
 case 0: return '.';
 case 1: return ',';
 case 2: return '-';
 case 3: return ';';
 case 4: return ':';
 case 5: return ' '; // se
 case 6: return '?';
 case 7: return '(';
 case 8: return ')';
 case 9: return '\\n'; // se

// punc  weak-punc  lit word-repl quasi-let quasi-math  ?serialize
// surround group word-scale code math vis dcode let diacritic-let s-ref-display

//  16 roles   


 case 10: ~   // circa    (word-repl)
 case 11: !   // punc
 case 12: @   // email, handles ...  (lit)
 case 13: #   // number   (lit) or (word-repl)
 case 14: $   // dollars  (lit) or (word-repl)
 case 15: %   // percent  (lit) or (word-repl)
 case 16: &   // part of name  (repl ^)  (lit)
 case 17: &   // not part of name   (word-repl)
 case 18: *   // polite    (quasi-letter)  (lit)
 case 19: (   // surround
 case 20: )   // surround
 case 21: -   // em dash   punc1
 case 22: =   // quasi-math
 case 23: +   // quasi-math
 case 24: [   // punc
 case 25: ]   // punc
 case 26: {   // group
 case 27: }   // group
 case 28: [   // group/surround 
 case 29: ]   // group/surround
 case 30: /   // punc      // case 30: ;
 case 31: /   // non-punc (quasi-let) or (word-scale)  // case 31: :
 case 32: '   // inch     (word-repl)
 case 33: "   // feet     (word-repl)
 case 34: '   // apos     (lit)
 case 35: <   // quasi-math
 case 36: \n  // se          (punc)
 case 37: >   // quasi-math 
 case 38: .   // num lit
 case 39: ?   // weak punc

 case 40: return '!'; // weak punc
 case 41: return '.'; // weak punc
 case 42: return '.'; // abr
 case 43: return '.'; // ell
 case 44: return '.'; // ellpn
 case 45: return '-'; // en dash
 case 46: return '-'; // sml
 case 47: return '-'; // quasi-math (neg)
 case 48: return '-'; // quasi-math (minus)
 case 49: return ','; // num lit
 case 50: return '\''; // print osq
 case 51: return '\'';  // print csq
 case 52: return '\"';  // print odq 
 case 53: return '\"';  // print cdq 
 case 54: return '';
 case 55: return '';
 case 56: return '';
 case 57: return '';
 case 58: return '';
 case 59: return '';
 case 60: return '';
 case 61: return '';
 case 62: return '';
 case 63: return '';

+10

128
  // code, math, vis
 case 0: ~
 case 1: !
 case 2: @
 case 3: #
 case 4: $
 case 5: %
 case 6: ^
 case 7: &
 case 8: *
 case 9: (
 case 10: )
 case 11: -
 case 12: =
 case 13: +
 case 14: [
 case 15: ]
 case 16: {
 case 17: }
 case 18: \
 case 19: |
 case 20: ;
 case 21: :
 case 22: '
 case 23: "
 case 24: ,
 case 25: <
 case 26: .
 case 27: >
 case 28: /
 case 29: ?

 case 30: \r
 case 31: \t

//++ 42

160
 + 32
//or 15 dia = +17 

0 \aaÐ
1 \DH* 
2 \L
3 \o
4 \ss
5 \AA
6 \dh* 
7 \l
8 \O
9 \SS
10 \AE
11 \DJ*
12 \NG*
13 \OE
14 \TH*
15 \ae
16 \dj*
­17 \ng*
18 \oe
19 \th*



192 ...
0: U+00C0 	À 	Latin Capital Letter A with grave 	
1: U+00C1 	Á 	Latin Capital letter A with acute 	
2: U+00C2 	Â 	Latin Capital letter A with circumflex 	
3: U+00C3 	Ã 	Latin Capital letter A with tilde 	
4: U+00C4 	Ä 	Latin Capital letter A with diaeresis 	
5: U+00C5 	Å 	Latin Capital letter A with ring above 	
6: U+00C6 	Æ 	Latin Capital letter AE 	
7: U+00C7 	Ç 	Latin Capital letter C with cedilla 	
8: U+00C8 	È 	Latin Capital letter E with grave 	
9: U+00C9 	É 	Latin Capital letter E with acute 	
10: U+00CA 	Ê 	Latin Capital letter E with circumflex 	
11: U+00CB 	Ë 	Latin Capital letter E with diaeresis 	
12: U+00CC 	Ì 	Latin Capital letter I with grave 	
13: U+00CD 	Í 	Latin Capital letter I with acute 	
14: U+00CE 	Î 	Latin Capital letter I with circumflex 	
15: U+00CF 	Ï 	Latin Capital letter I with diaeresis 	
16: U+00D0 	Ð 	Latin Capital letter Eth 	
17: U+00D1 	Ñ 	Latin Capital letter N with tilde 	
18: U+00D2 	Ò 	Latin Capital letter O with grave 	
19: U+00D3 	Ó 	Latin Capital letter O with acute 	
20: U+00D4 	Ô 	Latin Capital letter O with circumflex 	
21: U+00D5 	Õ 	Latin Capital letter O with tilde 	
22: U+00D6 	Ö 	Latin Capital letter O with diaeresis 	
23: U+00D8 	Ø 	Latin Capital letter O with stroke 	
24: U+00D9 	Ù 	Latin Capital letter U with grave 	
25: U+00DA 	Ú 	Latin Capital letter U with acute 	
26: U+00DB 	Û 	Latin Capital Letter U with circumflex 	
27: U+00DC 	Ü 	Latin Capital Letter U with diaeresis 	
28: U+00DD 	Ý 	Latin Capital Letter Y with acute 	
29: U+00DE 	Þ 	Latin Capital Letter Thorn 	
30: U+00DF 	ß 	Latin Small Letter sharp S 	
31: U+00E0 	à 	Latin Small Letter A with grave 	
32: U+00E1 	á 	Latin Small Letter A with acute 	
33: U+00E2 	â 	Latin Small Letter A with circumflex 	
34: U+00E3 	ã 	Latin Small Letter A with tilde 	
35: U+00E4 	ä 	Latin Small Letter A with diaeresis 	
36: U+00E5 	å 	Latin Small Letter A with ring above 	
37: U+00E6 	æ 	Latin Small Letter AE 	
38: U+00E7 	ç 	Latin Small Letter C with cedilla 	
39: U+00E8 	è 	Latin Small Letter E with grave 	
40: U+00E9 	é 	Latin Small Letter E with acute 	
41: U+00EA 	ê 	Latin Small Letter E with circumflex 	
42: U+00EB 	ë 	Latin Small Letter E with diaeresis 	
43: U+00EC 	ì 	Latin Small Letter I with grave 	
44: U+00ED 	í 	Latin Small Letter I with acute 	
45: U+00EE 	î 	Latin Small Letter I with circumflex 	
46: U+00EF 	ï 	Latin Small Letter I with diaeresis 	
47: U+00F0 	ð 	Latin Small Letter Eth 	
48: U+00F1 	ñ 	Latin Small Letter N with tilde 	
49: U+00F2 	ò 	Latin Small Letter O with grave 	
50: U+00F3 	ó 	Latin Small Letter O with acute 	
51: U+00F4 	ô 	Latin Small Letter O with circumflex 	
52: U+00F5 	õ 	Latin Small Letter O with tilde 	
53: U+00F6 	ö 	Latin Small Letter O with diaeresis 	
54: U+00F8 	ø 	Latin Small Letter O with stroke 	
55: U+00F9 	ù 	Latin Small Letter U with grave 	
56: U+00FA 	ú 	Latin Small Letter U with acute 	
57: U+00FB 	û 	Latin Small Letter U with circumflex 	
58: U+00FC 	ü 	Latin Small Letter U with diaeresis 	
59: U+00FD 	ý 	Latin Small Letter Y with acute 	
60: U+00FE 	þ 	Latin Small Letter Thorn 	
61: U+00FF 	ÿ 	Latin Small Letter Y with diaeresis 	









 case 10: return '.'; // abr
 case 11: return '.'; // dec
 case 12: return '.'; // ell
 case 13: return '.'; // ellpn
 case 14: return '.'; 

 case 15: return '-';
 case 16: return '-';
 case 17: return '-';
 case 18: return '-';
 case 19: return '-';

 case 20: return 'k';
 case 21: return 'l';
 case 22: return 'm';
 case 23: return 'n';
 case 24: return 'o';
 case 25: return 'p';
 case 26: return 'q';
 case 27: return 'r';
 case 28: return 's';
 case 29: return 't';
 case 30: return 'u';
 case 31: return 'v';
 case 32: return 'w';
 case 33: return 'x';
 case 34: return 'y';
 case 35: return 'z';
 case 36: return '_';
 case 37: return 'A';
 case 38: return 'B';
 case 39: return 'C';
 case 40: return 'D';
 case 41: return 'E';
 case 42: return 'F';
 case 43: return 'G';
 case 44: return 'H';
 case 45: return 'I';
 case 46: return 'J';
 case 47: return 'K';
 case 48: return 'L';
 case 49: return 'M';
 case 50: return 'N';
 case 51: return 'O';
 case 52: return 'P';
 case 53: return 'Q';
 case 54: return 'R';
 case 55: return 'S';
 case 56: return 'T';
 case 57: return 'U';
 case 58: return 'V';
 case 59: return 'W';
 case 60: return 'X';
 case 61: return 'Y';
 case 62: return 'Z';
 case 63: return ' ';


*/

u1 GH_Glyphdeck_Standard_8bit::get_default_void_separator()
{
 return 215;
}

u1 GH_Glyphdeck_Standard_8bit::get_default_null()
{
 return 247;
}

u4 GH_Glyphdeck_Standard_8bit::check_declared(u1 gp)
{
 if ( (gp >= 118) && (gp <= 124) )
 {
  return 1;
 }

 if(gp == 127)
   return 2;

 if(gp == 125)
   return 3;

 if(gp == 115)
   return 1; //?

 return 0;
}

u1 GH_Glyphdeck_Standard_8bit::encode_alt_pair(const QPair<u4, u4>& pr)
{
 if(pr.first == 0)
   return encode_latin1(pr.second);
 static QMap<QPair<u4, u4>, u1> static_map {{

   {{1, '-'}, 111}, // neg
   {{2, '-'}, 74}, // mdash
   {{3, '-'}, 112}, // minus
   {{4, '-'}, 101}, // ndash

   {{1, '_'}, 108}, // _ no escape
   {{2, '_'}, 106}, // ell (one ch se)
   {{3, '_'}, 118}, // _ decl s e


   {{1, '#'}, 109}, // # no escape

   {{1, '\''}, 180}, // osquote
   {{2, '\''}, 181}, // csquote
   {{3, '\''}, 96}, // ssquote

   {{1, '"'}, 182}, // odquote
   {{2, '"'}, 183}, // cdquote
   {{3, '"'}, 97}, // sdquote

   {{1, '?'}, 83}, // wp
   {{1, '@'}, 84}, // fiat letter

   {{1, '&'}, 103}, // ell between sentences

   {{1, '$'}, 106}, // ell (one ch)

   //?{{4, '.'}, 109}, // mdash

   {{1, '.'}, 104}, // wp
   {{2, '.'}, 105}, // abbr
   {{3, '.'}, 120}, // declare s end
   {{4, '.'}, 102}, // n lit

   {{1, ','}, 113}, // n lit

   {{3, ';'}, 119}, // _ decl s e

   {{3, '='}, 125}, //  decl s e
   {{3, '@'}, 126}, //  decl s s

   {{4, '~'}, 116}, //  s e
   {{3, ':'}, 121}, //  decl s e
   {{3, '*'}, 124}, //  decl s e
   {{4, '#'}, 123}, //  decl s e

   {{3, ','}, 122}, //  decl s e

   {{4, '('}, 184}, // group
   {{4, ')'}, 185}, // group

   {{3, '{'}, 145}, // group
   {{3, '}'}, 146}, // group

   {{4, '['}, 186}, // group
   {{4, ']'}, 187}, // group

   {{2, '{'}, 188}, // group
   {{2, '}'}, 189}, // group

   {{4, '<'}, 188}, // group
   {{4, '>'}, 189}, // group


   {{1, '*'}, 95}, // quasi let


}};

 u1 result = static_map.value(pr, get_default_null());

 return result;
}

u1 GH_Glyphdeck_Standard_8bit::encode_latin1(u1 chr)
{
 if(chr < 48)
   goto MainSwitch;
 if(chr < 58)
 {
  // // (48 - 57):  a digit
  return chr - 48;
 }
// else if(chr == 63)
// {
//  // question mark (?)
//  return 103;
// }
 else if(chr < 65)
 {
  goto MainSwitch;
  //return get_default_null();
 }
 else if(chr < 91)
 {
  // //   (A .. Z)
  return chr - 28;
 }
 else if(chr < 97)
 {
  goto MainSwitch;
 }
 else if(chr < 123)
 {
  // //   (a .. z)
  return chr - 87;
 }

MainSwitch:
 switch (chr)
 {
  //?
 case ':': return 67;   //ascii 58
 case ';': return 66;   //ascii 59

 case '<': return 93;   //ascii 60
 case '=': return 86;   //ascii 61
 case '>': return 94;   //ascii 62

 case '?': return 83;   //ascii 63

 case ' ': return 71;//
 case '\n': return 73;//
//? case '`': return 74; //64
 case '~': return 99; //64  //?
 case '!': return 75;
 case '@': return 76; //ascii 64
 case '#': return 77; //66
 case '$': return 78; //67
 case '%': return 79; //68  // hyphen
  //? case '^': return 80; //69
 case '&': return 80; //70
 case '*': return 95; //71
 case '(': return 68; //72
 case ')': return 69; //73

 case '-': return 63; //74  // NpMinus
 case '+': return 87; //76  // NpDot

 case '[': return 88; //77
 case ']': return 89; //78

 case '{': return 90; // no esc
 case '}': return 91; // no esc

 case '_': return 36;
 case '`': return 128;
 case '^': return 135;

 case '|': return 148; //86
 case '\\': return 92; //87

 case '\'': return 98; //90  // NsExc
 case '"': return 97; //91  // SnSp

 case ',': return 65; //92 // Boundary
 case '.': return 64; //94  // DashX
 case '/': return 82; //96  // OSqBrX


 default:
  return get_default_null();
 }

}

char GH_Glyphdeck_Standard_8bit::get_simple_encoding(u1 gp, QString& alternate)
{
 if(gp < 64)
   return get_basic_char(gp);

 if(gp >= 100)
   alternate = QString("`%1").arg(gp);
 else
   alternate = QString("|%1").arg(gp);

// switch(gp)
// {
// }
// alternate = "<?>";

 return '\0';
}


u1 GH_Glyphdeck_Standard_8bit::get_basic_char(u1 gp)
{
 gp &= 63;
 switch(gp)
 {
 case 0: return '0';
 case 1: return '1';
 case 2: return '2';
 case 3: return '3';
 case 4: return '4';
 case 5: return '5';
 case 6: return '6';
 case 7: return '7';
 case 8: return '8';
 case 9: return '9';
 case 10: return 'a';
 case 11: return 'b';
 case 12: return 'c';
 case 13: return 'd';
 case 14: return 'e';
 case 15: return 'f';
 case 16: return 'g';
 case 17: return 'h';
 case 18: return 'i';
 case 19: return 'j';
 case 20: return 'k';
 case 21: return 'l';
 case 22: return 'm';
 case 23: return 'n';
 case 24: return 'o';
 case 25: return 'p';
 case 26: return 'q';
 case 27: return 'r';
 case 28: return 's';
 case 29: return 't';
 case 30: return 'u';
 case 31: return 'v';
 case 32: return 'w';
 case 33: return 'x';
 case 34: return 'y';
 case 35: return 'z';
 case 36: return '_';
 case 37: return 'A';
 case 38: return 'B';
 case 39: return 'C';
 case 40: return 'D';
 case 41: return 'E';
 case 42: return 'F';
 case 43: return 'G';
 case 44: return 'H';
 case 45: return 'I';
 case 46: return 'J';
 case 47: return 'K';
 case 48: return 'L';
 case 49: return 'M';
 case 50: return 'N';
 case 51: return 'O';
 case 52: return 'P';
 case 53: return 'Q';
 case 54: return 'R';
 case 55: return 'S';
 case 56: return 'T';
 case 57: return 'U';
 case 58: return 'V';
 case 59: return 'W';
 case 60: return 'X';
 case 61: return 'Y';
 case 62: return 'Z';
 case 63: return '-';
 default: return '\0'; 
 }
}


u1 GH_Glyphdeck_Standard_8bit::get_boundary_whitespace_code(QString bws)
{
 if(bws == " ")
   return 117;

 return get_default_null();
}


u1 GH_Glyphdeck_Standard_8bit::get_char_with_diacritic(u1 gp)
{

}


u1 GH_Glyphdeck_Standard_8bit::get_non_alphanumeric_char(u1 gp)
{
 gp &= 63;
 switch(gp)
 {
 case 0: return '0';
 case 1: return '1';
 case 2: return '2';
 case 3: return '3';
 case 4: return '4';
 case 5: return '5';
 case 6: return '6';
 case 7: return '7';
 case 8: return '8';
 case 9: return '9';
 case 10: return 'a';
 case 11: return 'b';
 case 12: return 'c';
 case 13: return 'd';
 case 14: return 'e';
 case 15: return 'f';
 case 16: return 'g';
 case 17: return 'h';
 case 18: return 'i';
 case 19: return 'j';
 case 20: return 'k';
 case 21: return 'l';
 case 22: return 'm';
 case 23: return 'n';
 case 24: return 'o';
 case 25: return 'p';
 case 26: return 'q';
 case 27: return 'r';
 case 28: return 's';
 case 29: return 't';
 case 30: return 'u';
 case 31: return 'v';
 case 32: return 'w';
 case 33: return 'x';
 case 34: return 'y';
 case 35: return 'z';
 case 36: return '_';
 case 37: return 'A';
 case 38: return 'B';
 case 39: return 'C';
 case 40: return 'D';
 case 41: return 'E';
 case 42: return 'F';
 case 43: return 'G';
 case 44: return 'H';
 case 45: return 'I';
 case 46: return 'J';
 case 47: return 'K';
 case 48: return 'L';
 case 49: return 'M';
 case 50: return 'N';
 case 51: return 'O';
 case 52: return 'P';
 case 53: return 'Q';
 case 54: return 'R';
 case 55: return 'S';
 case 56: return 'T';
 case 57: return 'U';
 case 58: return 'V';
 case 59: return 'W';
 case 60: return 'X';
 case 61: return 'Y';
 case 62: return 'Z';
 case 63: return '-';
 default: return '\0'; 
 }
}

QString GH_Glyphdeck_Standard_8bit::get_latex_supplement(u1 gp, GH_Block_Base::Divert_Mode dm)
{
 if(gp == 72)
 {
  if(dm != GH_Block_Base::Divert_Sentence_Boundaries)
    return "\\>";
 }
 if(gp == 100)
 {
  if(dm != GH_Block_Base::Divert_Sentence_Boundaries)
    return "\\> ";
 }
 return {};
}

u1 GH_Glyphdeck_Standard_8bit::get_sentence_end_space_swap(u1 gp)
{
 if( (gp == 71) || (gp == 72) )
   return 72;

 if( (gp == 73) || (gp == 100) )
   return 100;

 if( (gp == 118) || (gp == 119) || (gp == 125) )
   return gp;

 return get_default_null();
}


u1 GH_Glyphdeck_Standard_8bit::get_sentence_end_swap(u1 gp)
{
 if(gp == 64)
   return 70;

 if( (gp == 115) || (gp == 116) || (gp == 83) || (gp == 75) || (gp == 70)  || (gp == 103) )
   return gp;

 if( (gp >= 120) && (gp <= 124) )
   return gp;

 return get_default_null();
}

void get_latex_64_to_117(u1 gp, QString& result)
{
 static QVector<QString> static_vec {{
   ".", // 64
   ",", // 65
   ";", // 66
   ":", // 67
   "(", // 68
   ")", // 69
   ".", // 70   se
   " ", // 71
   " ", // 72    se
   "\n", // 73
   "\\mdash{}", // 74 // se
   "!", // 75 // punc
   "@", // 76 // email, handles ...  (lit)
   "\\#", // 77 // number   (lit) or (word-repl)
   "$", // 78 // dollars  (lit) or (word-repl)
   "%", // 79 // percent  (lit) or (word-repl)
   "&", // 80 // part of name  (word-repl)
   "&", // 81 // not part of name  (colloq/subpunctuation)
   "/", // 82 // punc

   "?", // 83 // punc

   // 84 = start of sentence flag ...
   "{\\zfl}",

   "*", // 85 // polite
   "=", // 86 // (quasi math)
   "+", // 87 // (quasi math)

   "[", // 88 // (punc)
   "]", // 89 // (punc)

   "{", // 90 // lit
   "}", // 91 // lit

   "\\", // 92 // non-punc
   "<", // 93 // quasi-math
   ">", // 94 // quasi-math

   "*", // 95 // quasi math
   "\\ssquote", // 96 // ' feet
   "\\sdquote", // 97 // " inches
   "'", // 98 // (apos) punc
   "~", // 99 // (word-repl)
   "\n", // 100 //  se  64+36
   "\\ndash{}", // 101

   ".", // 102 // num literal

   "...", // 103 // // punc ell between sentence

   "...", // 104 // //? punc ell in sentence?

   ".", // 105 // abbr

   "\\txtdots{}", // 106 // ellipses (1 char)
   ".", // 107 // ellipses part (subpunc)

   "_", // 108 // no esc
   "#", // 109 // no esc
   "%", // 110 // no esc
   "$", // 111 // no esc
   "-", // 112 // quasi-math (neg)
   "-", // 113 // quasi-math (minus)
   ",", // 114 // quasi-math (lit)


   // 115 se suspend to par
   "{\\spsg}",
   // 116 = abnormal end of sentence flag ...
   "{\\efl}",

   "", // 117 // block boundary whitespace

//   "[", // 116 // surround
//   "]", // 117 // surround
   }};

 result = static_vec.value(gp - 64);
}

void get_latex_118_to_127(u1 gp, QString& result)
{
 // 118 = space se declare
 // 119 = \n se declare
 // 120 = . se declare
 // 121 = : se declare
 // 122 = , se declare

 static QVector<QString> static_vec {{
   " ", // 118
   "\n", // 119
   ".", // 120
   ":", // 121
   ",", // 122

   "{\\fiatse}", // 123 fiat (zero-width) se
   "{\\fiatses}", // 124 fiat (zero-width) ses

   "{\\sssg}", // 125 se suspend
   "{\\srsg}", // 126 ss resume

   "\n"  // 127   se widow
  }};

 result = static_vec.value(gp - 118);
}

void get_latex_128_to_159(u1 gp, QString& result)
{
 static QVector<QString> static_vec {{
   "`",  // 128
   "~", // 129
   "!", // 130
   "@", // 131
   "#", // 132
   "$", // 133
   "%", // 134
   "^", // 135
   "&", // 136
   "*", // 137
   "(", // 138
   ")", // 139
   "-", // 140
   "=", // 141
   "+", // 142
   "[", // 143
   "]", // 144
   "{", // 145
   "}", // 146
   "\\", // 147
   "|", // 148
   ";", // 149
   ":", // 150
   "'", // 151
   "\"", // 152
   ",", // 153
   "<", // 154
   ".", // 155
   ">", // 156
   "/", // 157
   "?", // 158
   "\\t", // 159
   }};

 result = static_vec.value(gp - 128);
}

void get_latex_160_to_179(u1 gp, QString& result)
{
 static QVector<QString> static_vec {{
   "\\aaÐ{}", // 160
   "\\DH*{}", // 161
   "\\L{}", // 162
   "\\o{}", // 163
   "\\ss{}", // 164
   "\\AA{}", // 165
   "\\dh*{}", // 166
   "\\l{}", // 167
   "\\O{}", // 168
   "\\SS{}", // 169
   "\\AE{}", // 170
   "\\DJ*{}", // 171
   "\\NG*{}", // 172
   "\\OE{}", // 173
   "\\TH*{}", // 174
   "\\ae{}", // 175
   "\\dj*{}", // 176
   "\\ng*{}", // 177
   "\\oe{}", // 178
   "\\th*{}", // 179
   }};

 result = static_vec.value(gp - 160);
}

void get_latex_180_to_189(u1 gp, QString& result)
{
 static QVector<QString> static_vec {{
   "\\osquote{}", // 180 // punc
   "\\csquote{}", // 181 // punc
   "\\odquote{}", // 182 // punc
   "\\cdquote{}", // 183 // punc

   "(", // 184 // surround
   ")", // 185 // surround

   "[", // 186 // surround
   "]", // 187 // surround

   "<", // 188 // surround
   ">", // 189 // surround
 }};

 result = static_vec.value(gp - 180);
 // unused
}

void get_latex_190_to_191(u1 gp, QString& result)
{
 // unused
}

#ifdef HIDE
   {1, "&Agrave;" }, // { "&#192;" }, Capital a with grave accent
   {1, "&Aacute;" }, // { "&#193;" }, Capital a with acute accent
   {1, "&Acirc;" }, // { "&#194;" }, Capital a with circumflex accent
   {1, "&Atilde;" }, // { "&#195;" }, Capital a with tilde
   {1, "&Auml;" }, // { "&#196;" }, Capital a with umlaut
   {1, "&Aring;" }, // { "&#197;" }, Capital a with ring
   {1, "&AElig;" }, // { "&#198;" }, Capital ae
   {1, "&Ccedil;" }, // { "&#199;" }, Capital c with cedilla
   {1, "&Egrave;" }, // { "&#200;" }, Capital e with grave accent
   {1, "&Eacute;" }, // { "&#201;" }, Capital e with acute accent
   {1, "&Ecirc;" }, // { "&#202;" }, Capital e with circumflex accent
   {1, "&Euml;" }, // { "&#203;" }, Capital e with umlaut
   {1, "&Igrave;" }, // { "&#204;" }, Capital i with grave accent
   {1, "&Iacute;" }, // { "&#205;" }, Capital i with accute accent
   {1, "&Icirc;" }, // { "&#206;" }, Capital i with circumflex accent
   {1, "&Iuml;" }, // { "&#207;" }, Capital i with umlaut
   {1, "&ETH;" },      //  {1, "&#208;" }, Capital eth (Icelandic)
   {1, "&Ntilde;" }, // { "&#209;" }, Capital n with tilde
   {1, "&Ograve;" }, // { "&#210;" }, Capital o with grave accent
   {1, "&Oacute;" }, // { "&#211;" }, Capital o with accute accent
   {1, "&Ocirc;" }, // { "&#212;" }, Capital o with circumflex accent
   {1, "&Otilde;" }, // { "&#213;" }, Capital o with tilde
   {1, "&Ouml;" }, // { "&#214;" }, Capital o with umlaut
   {1, "&Oslash;" }, // { "&#216;" }, Capital o with slash
   {1, "&Ugrave;" }, // { "&#217;" }, Capital u with grave accent
   {1, "&Uacute;" }, // { "&#218;" }, Capital u with acute accent
   {1, "&Ucirc;" }, // { "&#219;" }, Capital u with circumflex accent
   {1, "&Uuml;" }, // { "&#220;" }, Capital u with umlaut
   {1, "&Yacute;" }, // { "&#221;" }, Capital y with acute accent
   {1, "&THORN;" }, // { "&#222;" }, Capital thorn (Icelandic)
   {1, "&szlig;" }, // { "&#223;" }, Lowercase sharp s (German)
   {1, "&agrave;" }, // { "&#224;" }, Lowercase a with grave accent
   {1, "&aacute;" }, // { "&#225;" }, Lowercase a with acute accent
   {1, "&acirc;" }, // { "&#226;" }, Lowercase a with circumflex accent
   {1, "&atilde;" }, // { "&#227;" }, Lowercase a with tilde
   {1, "&auml;" }, // { "&#228;" }, Lowercase a with umlaut
   {1, "&aring;" }, // { "&#229;" }, Lowercase a with ring
   {1, "&aelig;" }, // { "&#230;" }, Lowercase ae
   {1, "&ccedil;" }, // { "&#231;" }, Lowercase c with cedilla
   {1, "&egrave;" }, // { "&#232;" }, Lowercase e with grave accent
   {1, "&eacute;" }, // { "&#233;" }, Lowercase e with acute accent
   {1, "&ecirc;" }, // { "&#234;" }, Lowercase e with circumflex accent
   {1, "&euml;" }, // { "&#235;" }, Lowercase e with umlaut
   {1, "&igrave;" }, // { "&#236;" }, Lowercase i with grave accent
   {1, "&iacute;" }, // { "&#237;" }, Lowercase i with acute accent
   {1, "&icirc;" }, // { "&#238;" }, Lowercase i with circumflex accent
   {1, "&iuml;" }, // { "&#239;" }, Lowercase i with umlaut
   {1, "&eth;" },   //  { "&#240;" }, Lowercase eth (Icelandic)
   {1, "&ntilde;" }, // { "&#241;" }, Lowercase n with tilde
   {1, "&ograve;" }, // { "&#242;" }, Lowercase o with grave accent
   {1, "&oacute;" }, // { "&#243;" }, Lowercase o with acute accent
   {1, "&ocirc;" }, // { "&#244;" }, Lowercase o with circumflex accent
   {1, "&otilde;" }, // { "&#245;" }, Lowercase o with tilde
   {1, "&ouml;" }, // { "&#246;" }, Lowercase o with umlaut
   {1, "&oslash;" }, // { "&#248;" }, Lowercase o with slash
   {1, "&ugrave;" }, // { "&#249;" }, Lowercase u with grave accent
   {1, "&uacute;" }, // { "&#250;" }, Lowercase u with acute accent
   {1, "&ucirc;" }, // { "&#251;" }, Lowercase u with circumflex accent
   {1, "&uuml;" }, // { "&#252;" }, Lowercase u with umlaut
   {1, "&yacute;" }, // { "&#253;" }, Lowercase y with acute accent
   {1, "&thorn;" }, // { "&#254;" }, Lowercase thorn (Icelandic)
   {1, "&yuml;" },     // &#255; Lowercase y with umlaut

#endif //def HIDE
void get_latex_192_to_255(u1 gp, QString& result)
{
 static QVector<QString> static_vec {{

   "\\`{A}", // 192  U+00C0 	À 	Latin Capital Letter A with grave
   "\\'{A}", // 193 U+00C1 	Á 	Latin Capital letter A with acute
   "\\^{A}", // 194 U+00C2 	Â 	Latin Capital letter A with circumflex
   "\\~{A}", // 195 U+00C3 	Ã 	Latin Capital letter A with tilde
   "\\\"{A}", // 196 U+00C4 	Ä 	Latin Capital letter A with diaeresis
   "\\AA{}", // 197 U+00C5 	Å 	Latin Capital letter A with ring above
   "\\AE{}", // 198 U+00C6 	Æ 	Latin Capital letter AE
   "\\s{C}", // 199 U+00C7 	Ç 	Latin Capital letter C with cedilla
   "\\`{E}", // 200 U+00C8 	È 	Latin Capital letter E with grave
   "\\'{E}", // 201 U+00C9 	É 	Latin Capital letter E with acute
   "\\^{E}", // 202 U+00CA 	Ê 	Latin Capital letter E with circumflex
   "\\\"{E}", // 203 U+00CB 	Ë 	Latin Capital letter E with diaeresis
   "\\`{I}", // 204 U+00CC 	Ì 	Latin Capital letter I with grave
   "\\'{I}", // 205 U+00CD 	Í 	Latin Capital letter I with acute
   "\\^{I}", // 206 U+00CE 	Î 	Latin Capital letter I with circumflex
   "\\\"{I}", // 207 U+00CF 	Ï 	Latin Capital letter I with diaeresis
   "\\DH{}", // 208 U+00D0 	Ð 	Latin Capital letter Eth
   "\\~{N}", // 209 U+00D1 	Ñ 	Latin Capital letter N with tilde
   "\\`{O}", // 210 U+00D2 	Ò 	Latin Capital letter O with grave
   "\\'{O}", // 211 U+00D3 	Ó 	Latin Capital letter O with acute
   "\\^{O}", // 212 U+00D4 	Ô 	Latin Capital letter O with circumflex
   "\\~{O}", // 213 U+00D5 	Õ 	Latin Capital letter O with tilde
   "\\\"{O}", // 214 U+00D6 	Ö 	Latin Capital letter O with diaeresis
   "\\nvoid{}", // 215 -- should never generate
   "\\Ostrok{}", // 216 U+00D8 	Ø 	Latin Capital letter O with stroke
   "\\`{U}", // 217 U+00D9 	Ù 	Latin Capital letter U with grave
   "\\'{U}", // 218 U+00DA 	Ú 	Latin Capital letter U with acute
   "\\^{U}", // 219 U+00DB 	Û 	Latin Capital Letter U with circumflex
   "\\\"{U}", // 220 U+00DC 	Ü 	Latin Capital Letter U with diaeresis
   "\\'{Y}", // 221 U+00DD 	Ý 	Latin Capital Letter Y with acute
   "\\TH{}", // 222 U+00DE 	Þ 	Latin Capital Letter Thorn
   "\\ss{}", // 223 U+00DF 	ß 	Latin Small Letter sharp S
   "\\`{a}", // 224 U+00E0 	à 	Latin Small Letter A with grave
   "\\'{a}", // 225 U+00E1 	á 	Latin Small Letter A with acute
   "\\^{a}", // 226 U+00E2 	â 	Latin Small Letter A with circumflex
   "\\~{a}", // 227 U+00E3 	ã 	Latin Small Letter A with tilde
   "\\\"{a}", // 228 U+00E4 	ä 	Latin Small Letter A with diaeresis
   "\\aa{}", // 229 U+00E5 	å 	Latin Small Letter A with ring above
   "\\ae{}", // 230 U+00E6 	æ 	Latin Small Letter AE
   "\\s{c}", // 231 U+00E7 	ç 	Latin Small Letter C with cedilla
   "\\`{e}", // 232 U+00E8 	è 	Latin Small Letter E with grave
   "\\'{e}", // 233 U+00E9 	é 	Latin Small Letter E with acute
   "\\^{e}", // 234 U+00EA 	ê 	Latin Small Letter E with circumflex
   "\\\"{e}", // 235 U+00EB 	ë 	Latin Small Letter E with diaeresis
   "\\`{i}", // 236 U+00EC 	ì 	Latin Small Letter I with grave
   "\\'{i}", // 237 U+00ED 	í 	Latin Small Letter I with acute
   "\\^{i}", // 238 U+00EE 	î 	Latin Small Letter I with circumflex
   "\\\"{i}", // 239 U+00EF 	ï 	Latin Small Letter I with diaeresis
   "\\dh{}", // 240 U+00F0 	ð 	Latin Small Letter Eth
   "\\~{n}", // 241 U+00F1 	ñ 	Latin Small Letter N with tilde
   "\\`{o}", // 242 U+00F2 	ò 	Latin Small Letter O with grave
   "\\'{o}", // 243 U+00F3 	ó 	Latin Small Letter O with acute
   "\\^{o}", // 244 U+00F4 	ô 	Latin Small Letter O with circumflex
   "\\~{o}", // 245 U+00F5 	õ 	Latin Small Letter O with tilde
   "\\\"{o}", // 246 U+00F6 	ö 	Latin Small Letter O with diaeresis
   "\\svoid{}", // 247 -- separator; should never generate
   "\\ostrok{}", // 248 U+00F8 	ø 	Latin Small Letter O with stroke
   "\\`{u}", // 249 U+00F9 	ù 	Latin Small Letter U with grave
   "\\'{u}", // 250 U+00FA 	ú 	Latin Small Letter U with acute
   "\\^{u}", // 251 U+00FB 	û 	Latin Small Letter U with circumflex
   "\\\"{u}", // 252 U+00FC 	ü 	Latin Small Letter U with diaeresis
   "\\'{y}", // 253 U+00FD 	ý 	Latin Small Letter Y with acute
   "\\th{}", // 254 U+00FE 	þ 	Latin Small Letter Thorn
   "\\\"{y}", // 255 U+00FF 	ÿ 	Latin Small Letter Y with diaeresis
   }};

 result = static_vec.value(gp - 192);
}




QString GH_Glyphdeck_Standard_8bit::get_latex_representation(u1 gp)
{
 if(gp == 36)
   return "\\_";
 static char the_char = '?';
 if(gp < 64)
 {
  the_char = get_basic_char(gp);
  return QString::fromLatin1(&the_char, 1);
 }

 QString result;
 if(gp < 118)
   get_latex_64_to_117(gp, result);
 else if(gp < 128)
   get_latex_118_to_127(gp, result);
 else if(gp < 160)
   get_latex_128_to_159(gp, result);
 else if(gp < 180)
   get_latex_160_to_179(gp, result);
 else if(gp < 190)
   get_latex_180_to_189(gp, result);
 else if(gp < 192)
   get_latex_190_to_191(gp, result);
 else
   get_latex_192_to_255(gp, result);
 return result;
}

GH_Block_Base::Evaluation_Codes GH_Glyphdeck_Standard_8bit::check_confirm_clear_inter_sentence_gap(u1 gp)
{
  // //  currently no neutral ...
 if(gp == 71)
   return GH_Block_Base::Evaluation_Codes::Confirm;
 if(gp == 73)
   return GH_Block_Base::Evaluation_Codes::Confirm;
 return GH_Block_Base::Evaluation_Codes::Refute;
}

GH_Block_Base::Evaluation_Codes GH_Glyphdeck_Standard_8bit::check_confirm_sentence_resume(u1 gp)
{
 if(gp == 126)
   return GH_Block_Base::Evaluation_Codes::Confirm;

 return
   GH_Block_Base::Evaluation_Codes::Refute;
}


GH_Block_Base::Evaluation_Codes GH_Glyphdeck_Standard_8bit::check_confirm_sentence_end(u1 gp, bool have_space)
{
 if( (gp == 118) || (gp == 119) || (gp == 124) )
   return GH_Block_Base::Evaluation_Codes::Confirm_Via_Declared;

  // //? 115?

 if(gp == 125)
   return GH_Block_Base::Evaluation_Codes::Confirm_Via_Declared_Suspend;


 // //  currently only use ')' as neutral
 if(gp == 69)
   return GH_Block_Base::Evaluation_Codes::Neutral;
 if(gp == 71)
   return have_space?
     GH_Block_Base::Evaluation_Codes::Confirm
     : GH_Block_Base::Evaluation_Codes::Space;
 if(gp == 72)
   return GH_Block_Base::Evaluation_Codes::Confirm;
 if(gp == 73)
   return GH_Block_Base::Evaluation_Codes::Confirm;
 return GH_Block_Base::Evaluation_Codes::Refute;
}

GH_Block_Base::SDI_Interpretation_Codes GH_Glyphdeck_Standard_8bit::get_sdi_interpretation_code(u1 gp)
{
 if(gp < 64)
   return GH_Block_Base::SDI_Interpretation_Codes::Letter;


 if(gp < 118)
 {
  switch (gp)
  {
  case 64: // .
  case 75:
  case 83:
   return GH_Block_Base::SDI_Interpretation_Codes::Potential_Sentence_End;

  case 84:
   return GH_Block_Base::SDI_Interpretation_Codes::Declared_Fiat_Letter;

  case 103: // ... between sentences
   return GH_Block_Base::SDI_Interpretation_Codes::Declared_Fiat_Letter_Sentence_End;


   //?
  case 116: return GH_Block_Base::SDI_Interpretation_Codes::Potential_Sentence_End;

  case 72:
   return GH_Block_Base::SDI_Interpretation_Codes::Sentence_End_Space;
  case 71:
  case 73:
   return GH_Block_Base::SDI_Interpretation_Codes::Potential_Sentence_End_Space;

  case 117:
   return GH_Block_Base::SDI_Interpretation_Codes::Hide_Ignore;
  default:
   return GH_Block_Base::SDI_Interpretation_Codes::GH_Interpretation;
  }
 }
 if(gp < 127)
 {
  switch (gp)
  {
  case 118:
  case 119:
  case 124:
   return GH_Block_Base::SDI_Interpretation_Codes::Declared_Sentence_End_Space;

  case 120:
  case 121:
  case 122:
  case 123:   
   return GH_Block_Base::SDI_Interpretation_Codes::Declared_Sentence_End;

  case 125:
   return GH_Block_Base::SDI_Interpretation_Codes::Declared_Sentence_End_Suspend_Space;

  case 115: // //?
  case 126:
   return GH_Block_Base::SDI_Interpretation_Codes::Declared_Sentence_Resume_Space;

  }
 }
 if(gp < 159)
   return GH_Block_Base::SDI_Interpretation_Codes::GH_Interpretation;
 if(gp < 179)
   return GH_Block_Base::SDI_Interpretation_Codes::Letter;
 if(gp < 192)
   return GH_Block_Base::SDI_Interpretation_Codes::GH_Interpretation;
 if(gp == get_default_null())
   return GH_Block_Base::SDI_Interpretation_Codes::Void_Null;
 if(gp == get_default_void_separator())
   return GH_Block_Base::SDI_Interpretation_Codes::Void_Null;
 return GH_Block_Base::SDI_Interpretation_Codes::Letter;
}


QString GH_Glyphdeck_Standard_8bit::get_xml_representation(u1 gp)
{
 return {}; 
}

QChar GH_Glyphdeck_Standard_8bit::get_qchar_representation(u1 gp, QString& alternate)
{
 return {}; 
}

QString GH_Glyphdeck_Standard_8bit::get_qstring_representation(u1 gp)
{
 return {}; 
}



