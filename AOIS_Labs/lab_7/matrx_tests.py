import unittest

from matrix import *


class testMatrix(unittest.TestCase):
    def setUp(self):
        self.m = MatrixOperations()

    def test_assign_word(self):
        self.m.assign_word(5, "0100100100100000")

        self.assertEqual("0100100100100000", self.m.fetch_word(5))

    def test_read_element(self):
        self.assertEqual(False, self.m.read_element(0, 0))

    def test_assign_element(self):
        self.m.assign_element(0, 0, True)

        self.assertEqual(True, self.m.read_element(0, 0))

    def test_collumn_conjunction(self):
        self.m.assign_row(4, "0000000000100000")

        self.m.assign_row(5, "0100100100100000")
        self.m.collumn_conjunction(4, 5, 6)

        self.assertEqual("0000000000100000", self.m.fetch_row(6))

    def test_collumn_sheffer(self):
        self.m.assign_row(4, "0000000000100000")

        self.m.assign_row(5, "0100100100100000")
        self.m.collumn_sheffer(4, 5, 6)

        self.assertEqual("1111111111011111", self.m.fetch_row(6))


    def test_repeat_source(self):
        self.m.assign_row(4, "0000000000100000")
        self.m.assign_row(5, "0100100100100000")
        self.m.collumn_repeat_source(4, 6)

        self.assertEqual("0000000000100000", self.m.fetch_row(6))


    def test_reverse_source(self):
        self.m.assign_row(4, "0000000000100000")
        self.m.assign_row(5, "0100100100100000")
        self.m.collumn_reverse_source(4, 6)

        self.assertEqual("1111111111011111", self.m.fetch_row(6))


    def test_closest_find_smaller(self):
        self.m.assign_word(5, "0100100100100000")
        self.m.assign_word(3, "0110110110101010")
        self.m.assign_word(7, "0100100100101010")

        self.m.processAB("010")

        self.m.assign_word(10, "0111111111111111")
        self.m.assign_word(11, "0000000000000011")
        self.m.assign_word(12, "0111011011011111")
        self.assertEqual(
            ("0000000000000000", 0), self.m.closest_find("0110110110101010", False)
        )

    def test_processAB(self):
        self.m.assign_word(5, "0100100100100000")
        self.m.assign_word(3, "0110110110101010")
        self.m.assign_word(7, "0100100100101010")

        self.m.processAB("010")

        self.assertEqual("0100100100101101", self.m.fetch_word(5))
        self.assertEqual("0110110110101010", self.m.fetch_word(3))

    def test_closest_find_bigger(self):
        self.m.assign_word(5, "0100100100100000")
        self.m.assign_word(3, "0110110110101010")
        self.m.assign_word(7, "0100100100101010")

        self.m.processAB("010")

        self.m.assign_word(10, "0111111111111111")
        self.m.assign_word(11, "0000000000000011")
        self.m.assign_word(12, "0111011011011111")

        self.assertEqual(
            ("0110110110101010", 3), self.m.closest_find("0000000000000001", True)
        )







if __name__ == "__main__":
    unittest.main()
