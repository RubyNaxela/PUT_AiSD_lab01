#ifndef ALGORYTMY_CPP_ALGORITHMS_HPP
#define ALGORYTMY_CPP_ALGORITHMS_HPP

#include <algorithm>
#include <utility>

namespace sorts {

    void selection_sort(int* tab, int n) {
        for (int i = 0; i < n - 1; i++) {
            int temp_min = tab[i];
            int index = i;
            for (int j = i + 1; j < n; j++) {
                if (tab[j] < tab[i] && tab[j] < temp_min) {
                    index = j;
                    temp_min = tab[j];
                }
            }
            std::swap(tab[i], tab[index]);
        }
    }

    void bubble_sort(int* tab, int n) {
        bool sorted;
        for (int i = 0; i < n; i++) {
            sorted = true;
            // Pętla zatrzymuje się przez indeksem n-1, ponieważ za nim tablica jest już posortowana
            for (int j = 0; j < n - i - 1; j++) {
                if (tab[j] > tab[j + 1]) {
                    std::swap(tab[j], tab[j + 1]);
                    sorted = false;
                }
            }
            // Jesli petla nie wykonala zadnej zamiany, algorytm sie konczy
            if (sorted) return;
        }
    }

    void insertion_sort(int* tab, int n) {
        for (int key_index = 1; key_index < n; key_index++) {
            int key = tab[key_index];
            int j;
            for (j = key_index - 1; key < tab[j] && j >= 0; j--)
                std::swap(tab[j + 1], tab[j]);
            tab[j + 1] = key;
        }
    }

    void merge_sort(int* src, int* res, int l, int p) {
        int sr = (l + p + 1) / 2; // Srodek tablicy
        // Wykonanie merge sort dla tablic skladowych
        if (sr - l > 1) merge_sort(src, res, l, sr - 1);
        if (p - sr > 0) merge_sort(src, res, sr, p);
        // Zlozenie tablic skladowych
        int r = l, q = sr;
        for (int i = l; i <= p; i++) res[i] = ((r == sr) || ((q <= p) && (src[r] > src[q]))) ? src[q++] : src[r++];
        for (int i = l; i <= p; i++) src[i] = res[i];
    }

    void merge_sort(int* tab, int n) {
        int* result = new int[n];
        merge_sort(tab, result, 0, n - 1);
        *tab = *result;
    }

    void quick_sort(int* tab, int l, int p) {
        if (p <= l) return; // Przypadek trywialny, gdy fragment tablicy ma 1 element
        int i = l - 1, j = p + 1;
        int c = tab[(l + p) / 2]; // Element rozdzielajacy
        while (true) {
            while (c > tab[++i]); // Dopoki nie znajdzie wiekszego lub rownego po prawej
            while (c < tab[--j]); // Dopoki nie znajdzie mniejszego lub rownego po lewej
            if (i <= j) std::swap(tab[i], tab[j]); // Jesli i oraz j sie nie spotkaly / minely, zamien je miejscami
            else break;
        }
        // Podzial tablicy na dwie czesci
        if (j > l) quick_sort(tab, l, j);
        if (i < p) quick_sort(tab, i, p);
    }

    void quick_sort(int* tab, int n) {
        quick_sort(tab, 0, n - 1);
    }

    void shell_sort(int* tab, int n) {
        // Wyznaczanie wartosci poczatkowego przesuniecia
        int h;
        for (h = 1; h < n; h = 3 * h + 1);
        h /= 9;
        // Sortowanie; powtarzanie czynnosci dla coraz wiekszych tablic
        while (h > 0) {
            for (int j = n - h - 1; j >= 0; j--) {
                int x = tab[j];
                int i = j + h;
                while (i < n && x > tab[i]) {
                    tab[i - h] = tab[i];
                    i += h;
                }
                tab[i - h] = x;
            }
            h /= 3;
        }
    }

    void counting_sort(int* tab, int n) {
        int t1[n];
        const int max = *std::max_element(tab, tab + n);
        int count[max]; // Tablica liczników
        for (int i = 0; i <= max; i++) count[i] = 0;
        for (int i = 0; i < n; i++) count[tab[i]]++; // Zliczanie elemenów
        // Zamiana histogramu na pozycje w tablicy
        for (int i = 1; i <= max; i++) count[i] += count[i - 1];
        // Budowa tablicy na podstawie wyznaczonej mapy pozycji
        for (int i = 0; i < n; i++) {
            t1[count[tab[i]] - 1] = tab[i];
            count[tab[i]]--;
        }
        // Przepisanie tablicy na podany wskaźnik
        for (int i = 0; i < n; i++) tab[i] = t1[i];
    }

    void heap_sort(int* tab, int n) {
        int j, k, x;
        // Budowanie kopca
        for (int i = 1; i < n; i++) {
            j = i;
            k = (j + 1) / 2;
            x = tab[i];
            // Przypisanie gornemu miejscu w kopcu dwoch nizszych
            while (k > 0 && tab[k - 1] < x) {
                tab[j] = tab[k - 1];
                j = k - 1;
                k = (j + 1) / 2;
            }
            tab[j] = x;
        }
        // Rozbieranie kopca
        for (int i = n - 1; i > 0; i--) {
            // Wstawienie najwiekszego elementu na koniec kopca i usuniecie go z niego
            std::swap(tab[0], tab[i]);
            j = 1;
            k = 2;
            int m;
            while (k < i + 1) {
                if (k + 1 < i && tab[k] > tab[k - 1]) m = k + 1;
                else m = k;
                if (tab[m - 1] <= tab[j - 1]) break;
                std::swap(tab[j - 1], tab[m - 1]);
                j = m;
                k = 2 * j;
            }
        }
    }
}

#endif //ALGORYTMY_CPP_ALGORITHMS_HPP