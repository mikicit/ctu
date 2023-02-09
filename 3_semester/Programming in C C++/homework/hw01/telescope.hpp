#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>

// --------------------- STAGE 1 ---------------------
/*
 * Analyzuje matici ze vstupniho proudu.
 * Format vstupniho proudu:
 *      - jeden radek v proudu je jeden radek v matici,
 *      - sloupce jsou oddeleny libovolnou mezerou mimo znak konce radku.
 *
 * Funkce vrati rozmery matice jako dvojici, pricemz prvni prvek je pocet radku a druhy pocet sloupcu.
 * Prazdny proud odpovida matici o rozmerech {0, 0}.
 * Matice s nekonzistentnim poctem prvku na radcich by mela vyvolat vyjimku std::invalid_argument.
 */
std::pair<size_t, size_t> parse_matrix(std::istream& in);

/*
 * Matici celych cicel ze vstupniho proudu nactete do jednorozmerneho vektoru.
 * Zachovejte format vstupu a vystupu z predchozi funkce.
 */
std::vector<int> parse_matrix(std::istream& in, const std::pair<size_t, size_t>& m_size);

/*
 * Vypiste matici do tabulky.
 * Sloupce mají stejnou sirku a sirka se rovná nejdelsimu vypisovanemu cislu + 2 (mezera vlevo a vpravo).
 * Cisla jsou zarovnana spravne.
 *
 * Priklad:
 * Matice rozmeru 2x3 zapsana ve vektoru { 1, -25, 1000, -1400, 15, -789 }:
 * -------------------------
 * |     1 |   -25 |  1000 |
 * | -1400 |    15 |  -789 |
 * -------------------------
 */
void print_matrix(std::ostream& out, const std::pair<size_t, size_t>& m_size, const std::vector<int>& vec);

// --------------------- STAGE 2 ---------------------
/*
 * Matici znaku (unsigned char) ze vstupniho proudu nactete do jednorozmerneho vektoru.
 * Ctete radne i "bile znaky", tj. mezery.
 * Nekonzistentni pocet prvku (neodpovida rozmerum matice] na vstupu by melo
 * vyvolat vyjimku std::invalid_argument.
 */
std::vector<unsigned char> parse_stream(std::istream& in, const std::pair<size_t, size_t>& m_size);

/*
 * Rotujte matici znaku o jeden radek dolu.
 *
 * Priklad:
 * Matice rozmetu 3x4 ve vektoru {'a', 'a', 'a', 'a', 'b', 'b', 'b', 'b', 'c', 'c', 'c', 'c'}
 * se rotuje do tvaru:
 * {'c', 'c', 'c', 'c', 'a', 'a', 'a', 'a', 'b', 'b', 'b', 'b'}
 */
void rotate_down(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec);

/*
 * Rotujte matici znaku o step radku dolu.
 *
 * Pokud je step zaporne, rotujeme smerem nahoru.
 * Pokud je step nulove, rotace neprobehne.
 * step muze byt vetsi nez pocet radku. V tomto pripade optimalizujte vypocet.
 */
void rotate_down(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, int step);

/*
 * Rotujte matici znaku o jeden sloupec doprava.
 *
 * Priklad:
 * Matice rozmetu 3x4 ve vektoru {'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd'}
 * se rotuje do tvaru:
 * {'d', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c'}
 */
void rotate_right(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec);

/*
 * Rotujte matici znaku o step sloupcu doprava.
 *
 * Pokud je step zaporne, rotujeme smerem doleva.
 * Pokud je step nulove, rotace neprobehne.
 * step muze byt vetsi nez pocet sloupcu. V tomto pripade optimalizujte vypocet.
 */
void rotate_right(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, int step);

/*
 * Deklarace bodu.
 * Bod jednoduse definujeme Point(2, 3) - bod [2, 3].
 */
struct Point {
    size_t x, y;
    Point(size_t xx, size_t yy) : x(xx), y(yy) {};
};

/*
 * Prohodte dva body p1 a p2 v matici znaku.
 *
 * Nekonzistentne zadane body (mimo rozmery matice) vyvolaji vyjimku std::invalid_argument.
 */
void swap_points(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, const Point& p1, const Point& p2);

/*
 * Prohodte dva stejne velke obdelniky v matici znaku.
 * Body p1 a p2 urcuji souradnice levych hornich rohu obdelniku.
 * Velikost obdelniku (sirka a vyska) je dana bodem delta.
 *
 * Nekonzistentne zadane obdelniky (mimo rozmery matice nebo obdelniky, ktere se prekryvaji)
 * vyvolaji vyjimku std::invalid_argument.
 *
 * Priklad:
 * Matice rozmetu 3x4 ve vektoru {'b', 'b', 'a', 'a', 'b', 'b', 'a', 'a', 'a', 'a', 'a', 'a'}
 * se prohozenim pro body p1 = [0, 0], p2 = [2, 1], delta = [2, 2] zmeni na matici:
 * {'a', 'a', 'a', 'a', 'a', 'a', 'b', 'b', 'a', 'a', 'b', 'b'}
 */
void swap_points(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, const Point& p1, const Point& p2, const Point& delta);

// --------------------- STAGE 3 ---------------------

/*
 * Dekodujte zadany obrazek.
 * Proces dekodovani je definovan v souboru s nazvem file. Jednotlive radky souboru popisuji cely proces:
 * r        - rotace doprava o jeden sloupec
 * r cis    - rotace doprava o cis sloupcu
 * l        - rotace doleva o jeden sloupec
 * l cis    - rotace doleva o cis sloupcu
 * d        - rotace dolu o jeden radek
 * d cis    - rotace dolu o cis radku
 * u        - rotace nahoru o jeden radek
 * u cis    - rotace nahoru o cis radku
 * s p1 p2  - prohodi body p1 a p2
 * s p1 p2 delta    - prohodi dva obdelniky, jejich leve horni rozhy jsou p1 a p2, delta je velikost obdelniku
 *
 * Soubor file otevrete a postupne ctete jeho jednotlivy radky.
 * Podle popisu na radku dekodujte obrazec zadany parametrem vec.
 * Spravnost dekodovani doporucujeme overit i vizualne - testy ukladaji vytvorene obrazky. Pokud tyto davaji smysl,
 * lze predpokladat, ze dekodovani probiha spravne.
 */
void decode_picture(const std::string& file, const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec);
