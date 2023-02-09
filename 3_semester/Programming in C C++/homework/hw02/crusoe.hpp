#ifndef PJC_GRAPH_HPP
#define PJC_GRAPH_HPP

#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

// ------------------- stage 1 -------------------
/*
 * Trida - vrchol grafu
 *
 * Vrchol grafu je dan:
 *  - souradnicemi bodu [x, y] - bod bude v obrazku SVG vykreslen an techto souradnicich,
 *  - name - nazev vrcholu, vypisuje se na obrazku SVG, doporucujeme poradove cislo vrcholu,
 *  - c_forward - barva popredi vrchodu (obvykle obrys obrazce)
 *  - neighbours - seznam sousednich vrcholu
 * Soused vrcholu je dan:
 *  - poradovym cislem vrcholu (typu size_t - viz definice grafu)
 *  - barvou hrany mezi vrcholem a jeho sousedem (typ std::string)
 */

class vertex {
private:
    std::pair<int, int> xy;
    std::string name, c_forward;
    std::vector<std::pair<size_t, std::string>> neighbours;
public:
    //! Vytvari vrchol podle danych parametru
    vertex();
    vertex(std::string str, int x, int y, std::string col = "#000000");
   /*
     * Prida vrchol s cislem vv mezi sousedy vrcholu
     * col - barva hrany mezi aktualnim vrcholem a sousedem vv
     *
     * Vrati true, pokud vrchol byl vlozen mezi sousedy, jinak vrati false
     */
    bool add_neighbour(size_t vv, const std::string& col = "#000000");
    /*
     * Vrati seznam sousedu daneho vrcholu
     */
    std::vector<std::pair<size_t, std::string>> get_neighbour() const;
    /*
     * Vrati souradnice x a y aktualniho vrcholu
     */
    std::pair<int, int> get_xy() const;
    /*
     * Nastavi barvu vrcholu na col
     */
    void set_color(const std::string& col);
    /*
     * Vrati aktualni barvu vrcholu
     */
    std::string get_color() const;
    /*
     * Nastavi barvu hrany mezi aktualnim vrcholem a vrcholem vv na col
     */
    void set_edge_color(size_t vv, const std::string& col);
    /*
     * Vrati barvu hrany mezi aktualnim vrcholem a vrcholem vv, pokud hrana existuje.
     * Jinak vrati "#FFFFFF"
     */
    std::string get_edge_color(size_t vv);
    /*
     * Operator zapisu do proudu je reprezentovan nize, doporucujeme jej neupravovat
     */
    friend std::ostream& operator<<(std::ostream& out, const vertex& v) {
        int x = v.xy.first;
        int y = v.xy.second;
        out << "<circle cx=\"" << x << "\" cy=\"" << y << R"(" r="7" )";
        out << "stroke=\"" << v.c_forward << R"(" stroke-width="2" fill="#C0C0C0" />)" << std::endl;
        out << "<text x=\"" << x << "\" y=\"" << y + 3 << R"(" text-anchor="middle" font-size="9" >)";
        out << v.name << "</text>\n";
        return out;
    };
};

/*
 * Trida - graf
 *
 * Graf je dan vrcholy vertices
 * num_elem je aktualni pocet vrcholu v grafu
 */
class graph {
private:
    std::vector<vertex> vertices;
    size_t num_elem = 0;
public:
    /*
     * Prida vrchol na souradnicich [x, y] s barvou col do grafu
     *  - name je vygenerovano automaticky, idealne cislo vrcholu
     */
    void add_vertex(int x, int y, const std::string& col = "#000000");
    /*
     * Prida hranu mezi vrcholy v1 a v2 do grafu
     *  - col - barva hrany
     */
    void add_edge(size_t v1, size_t v2, const std::string& col = "#000000");
    /*
     * Vrati true, pokud hrana mezi vrcholy v1 a v2 existuje
     * Jinak vrati false
     */
    bool is_edge(size_t v1, size_t v2) const;
    /*
     * Vrati barvu hrany mezi vrcholy v1 a v2 nebo "#FFFFFF" pokud hrana neexistuje
     */
    std::string edge_color(size_t v1, size_t v2) const;
    /*
     * Vrati barvu vrcholu v1 nebo "#FFFFFF" pokud vrchol neexistuje
     */
    std::string vertex_color(size_t v1) const;
    /*
     * Nastavi barvu col vrcholu v1
     */
    void set_vertex_color(size_t v1, const std::string& col);
    /*
     * Nastavi barvu col hrane mezi vrcholy v1 a v2
     */
    void set_edge_color(size_t v1, size_t v2, const std::string& col);

    /*
     * Zjisti, zda je graf prazdny, tj. neobsahuje zadne vrcholy
     */
    bool empty() const;
    /*
     * Vrati pocet vrcholu grafu
     */
    size_t size() const;
    /*
     * Zjisti pocet hran grafu
     */
    size_t num_edge() const;

// ------------------- stage 2 -------------------

    /*
     * Vrati vrchol s indexem num z pole vertices
     */
    vertex get_vertex(size_t num) const;
    /*
     * Zjisti vrcholy, ktere jsou dosazitelne z vrcholu from
     * Vrchol v je dosazitelny z from, pokud existuje cesta v grafu z v do from
     * Ulohou je zjistit komponentu grafu, ktera obsahuje vrchol from
     *
     * Vysledek je ulozen do pole achieved
     */
    void is_achievable(size_t from, std::vector<size_t>& achieved);
    /*
     * Obarvi komponentu grafu zjistenou predchozi metodou
     * Barvou col se obarvi vrcholy i hrany komponenty
     */
    void color_component(std::vector<size_t> cmp, const std::string& col);
    /*
     * Vrati cestu mezi vrcholy v1 a v2 v grafu, pokud cesta existuje
     * Cesta je definovana jako posloupnost vrcholu:
     * - prvnim vrcholem cesty je v1,
     * - poslednim vrcholem cesty je V2,
     * - ostatni vrcholy jsou v ceste serazeny postupne, jak je nutne je na ceste navstivit.
     *
     * Pokud cesta nenexistuje, vrati prazdny vector typu size_t
     *
     * Nalezena cesta by mela byt nejkratsi mozna.
     * Pokud cest existuje vice, nezalezi na tom, ktera z nich bude nalezena.
     * Testovana je vysledna delka cesty a jeji pruchodnost grafem.
     */
    std::vector<size_t> path(size_t v1, size_t v2);
    /*
     * Obarvi cestu grafu zjistenou predchozi metodou
     * Barvou col se obarvi vsechny hrany cesty. Vrcholy se neobravuji!
     */
    void color_path(std::vector<size_t> pth, const std::string& col);

// ------------------- stage 3 -------------------

    /*
     * Trida - vsechny komponenty grafu
     *
     * Triba obsahuje dva atributy:
     *  - odkaz na graf, pro ktery jsou komponenty vytvorene
     *  - jednotlive komponenty grafu zjistene metodou is_achievable
     * Komponenta grafu je typu std::vector<size_t>, vsechny komponenty jsou ulozeny ve struture std::vector.
     */
    class graph_comp {
    private:
        graph& gg;
        std::vector<std::vector<size_t>> components;
    public:
        /*
         * Kontruktor tridy - inicializuje vsechny atributy tridy
         */
        explicit graph_comp(graph& gg);
        /*
         * Obarvi jednotlive komponenty grafu. Vyuziva metodu color_component.
         *
         * Lze vyuzit pole:
         * std::vector<std::string> colors{"red", "olive", "orange", "lightblue", "yellow", "pink", "cyan", "purple", "brown", "magenta"};
         * Komponenty 0 az 9 budou postupne obarveny barvami z pole. Pro dalsi kompomenty vyuzijeme barvy v poli opakovane, tj.
         * komponenta 10 bude obarvena barvou "red", komponenta 11 bavou "olive" apod.
         *
         * Doporucujeme komponenty obsahujici pouze jeden vrchol nebarvit
         *
         * Obarveni komponent ovlivni vysledne SVG obrazky
         */
        void color_componennts();
        /*
         * Zjisti celkovy pocet komponent grafu
         */
        size_t count() const;
        /*
         * Zjisti celkovy pocet komponent grafu mimo komponenty obsahujici pouze jeden vrchol
         */
        size_t count_without_one() const;
        /*
         * Zjisti index v std::vector komponenty, která obsahuje maximalni pocet vrcholu (nejvetsi komponeneta)
         */
        size_t max_comp() const;
        /*
         * Zjisti velikost (pocet vrcholu) i-te komponenty
         */
        size_t size_of_comp(size_t i) const;
        /*
         * Vrati i-tou komponenty
         */
        std::vector<size_t> get_component(size_t i) const;
        /*
         * Zjisti, zda vrcholy v1 a v2 se nachazi ve stejne komponente grafu
         *
         * Pokud se v1 a v2 nachazi ve stejne komponente grafu, funkce vrati true. Tehdy existuje cesta mezi v1 a v2
         */
        bool same_comp(size_t v1, size_t v2) const;
    };
    /*
     * Trida - ohranicene oblasti
     *
     * Triba obsahuje dva atributy:
     *  - odkaz na graf, pro ktery oblast vytvarena
     *  - fence - ohrada obsahuje vsechny vrcholy do jiste vzdalenosti od vybraneho vrcholu
     */
    class graph_fence {
    private:
        graph& gg;
        std::vector<size_t> fence;
    public:
        /*
         * Kontruktor tridy - inicializuje vsechny atributy tridy
         *
         * Promenna fence bude obsahovat vrchol vv a vsechny vrcholy, jejichz vzdalenost (delka cesty) od vrcholu vv
         * je mensi nebo rovna distance - vzi zadani a ukazka na Courseware
         */
        explicit graph_fence(graph& gg, size_t vv, size_t distance);
        /*
         * Obarvi vsechny vrcholy v "ohrade" fence barvou col.
         * Metoda hrany grafu neobarvuje!
         */
        void color_fence(const std::string& col);
        /*
         * Vrati pocet vrcholu v ohrade
         */
        size_t count_stake() const;
        /*
         * Vrati i-ty vrchol ohrady
         * Pokud takový vrchol neexistuje, vrati -1
         */
        size_t get_stake(size_t i) const;
    };

    /*
     * Operator zapisu do proudu je reprezentovan nize, doporucujeme ho neupravovat
     */
    friend std::ostream& operator<<(std::ostream& out, const graph& g) {
        out << R"(<svg viewBox='0 0 500 500' xmlns='http://www.w3.org/2000/svg'>)" << std::endl;
        for (size_t v1 = 0; v1 < g.size(); ++v1)
            for (size_t v2 = v1 + 1; v2 < g.size(); ++v2) {
                if (g.is_edge(v1, v2)) {
                    std::pair<int, int> vv = g.vertices[v1].get_xy();
                    out << "<line x1=\"" << vv.first << "\" y1=\"" << vv.second << "\" ";
                    vv = g.vertices[v2].get_xy();
                    out << "x2=\"" << vv.first << "\" y2=\"" << vv.second << "\" stroke=\"" << g.edge_color(v1, v2) << "\" />\n";
                }
            }
        for (auto &el: g.vertices)
            out << el;
        out << R"(</svg>)" << std::endl;
        return out;
    };
};

#endif
