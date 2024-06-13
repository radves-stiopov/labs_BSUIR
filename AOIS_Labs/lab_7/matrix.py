from typing import List


class MatrixOperations:
    def __init__(self):
        self.matrix = self.make_matrix()

    @staticmethod
    def make_matrix() -> List[List[bool]]:
        matrix = []
        for i in range(16):
            row = []
            for j in range(16):
                row.append(False)
            matrix.append(row)

        return matrix

    def fetch_row(self, i: int) -> str:
        return "".join(str(int(self.read_element(j, i))) for j in range(16))

    def display_matrix(self) -> None:
        for row in self.matrix:
            print(" ".join(map(str, map(int, row))))

    def assign_row(self, i: int, word: str) -> None:
        if len(word) != 16:
            raise Exception("Неверная длина строки")
        for j in range(16):
            self.assign_element(j, i, bool(int(word[j])))

    def fetch_word(self, i: int) -> str:
        return "".join(str(int(self.read_element(i, j))) for j in range(16))

    def assign_word(self, i: int, word: str) -> None:
        if len(word) != 16:
            raise Exception("Неверная длина строки")
        for j in range(16):
            self.assign_element(i, j, bool(int(word[j])))

    def read_element(self, i: int, j: int) -> bool:
        return self.matrix[(i + j) % 16][i % 16]

    def assign_element(self, i: int, j: int, val: bool) -> None:
        self.matrix[(i + j) % 16][i % 16] = val

    def collumn_repeat_source(self, source: int, target: int) -> None:
        for i in range(16):
            res = self.read_element(i, source)
            self.assign_element(i, target, res)

    def collumn_reverse_source(self, source: int, target: int) -> None:
        for i in range(16):
            res = not self.read_element(i, source)
            self.assign_element(i, target, res)

    def collumn_conjunction(self, source_1: int, source_2: int, target: int) -> None:
        for i in range(16):
            res = self.read_element(i, source_1) and self.read_element(i, source_2)
            self.assign_element(i, target, res)

    def collumn_sheffer(self, source_1: int, source_2: int, target: int) -> None:
        for i in range(16):
            res = not (
                self.read_element(i, source_1) and self.read_element(i, source_2)
            )
            self.assign_element(i, target, res)

    def processAB(self, start_values: str) -> None:
        if len(start_values) != 3:
            raise Exception("Неверная длина подаваемого значения")

        start_bools = [bool(int(c)) for c in start_values]
        for x in range(16):
            if [self.read_element(x, i) for i in range(3)] == start_bools:
                self._sum_values(x)

    def _sum_values(self, word_ind: int) -> None:
        word = self.fetch_word(word_ind)
        field = []
        overflow = False

        for i in range(4):
            a, b = int(word[6 - i]), int(word[10 - i])
            sum_val = a + b + overflow
            field.append(sum_val % 2)
            overflow = sum_val > 1

        field.append(int(overflow))

        field = field[::-1]
        res = word[0:11]
        field_str = "".join(map(str, field))

        res += field_str

        self.assign_word(word_ind, res)

    def closest_find(self, a_word: str, is_up: bool) -> tuple:
        if len(a_word) != 16:
            raise Exception("Неверная длина подаваемого значения")

        comparative_words = [
            (self.fetch_word(i), i)
            for i in range(16)
            if self._compare(a_word, self.fetch_word(i), not is_up)
        ]

        if len(comparative_words) == 0:
            raise Exception("Нет таких слов")

        closest_ind = 0
        closest_word = comparative_words[0][0]

        for i in range(1, len(comparative_words)):
            word = self.fetch_word(i)
            if self._compare(closest_word, word, not is_up):
                closest_ind = i
                closest_word = comparative_words[i][0]

        return closest_word, comparative_words[closest_ind][1]

    def _compare(self, a_word: str, word: str, is_bigger: bool):
        g_var: List[bool] = [False for _ in range(17)]
        l_var: List[bool] = [False for _ in range(17)]
        for i in range(15, -1, -1):
            a_var = a_word[15 - i] == "1"
            word_var = word[15 - i] == "1"
            g_var[i] = g_var[i + 1] or ((not a_var) and word_var and (not l_var[i + 1]))
            l_var[i] = l_var[i + 1] or (a_var and (not word_var) and (not g_var[i + 1]))
        if is_bigger:
            return g_var[0] is False and l_var[0] is True
        else:
            return g_var[0] is True and l_var[0] is False
