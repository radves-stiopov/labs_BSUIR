from matrix import MatrixOperations

if __name__ == "__main__":
    m = MatrixOperations()
    m.assign_row(4, "0000000000100000")
    m.assign_row(5, "0100100100100000")
    m.collumn_conjunction(4, 5, 6)

    m.assign_row(7, "0100101101101000")
    m.collumn_sheffer(6, 7, 8)

    m.collumn_repeat_source(8, 9)

    m.collumn_reverse_source(8, 10)

    m.display_matrix()
    print("\nAB\n")

    mAB = MatrixOperations()
    mAB.assign_word(5, "0100100100100000")
    mAB.assign_word(3, "0110110110101010")
    mAB.assign_word(7, "0100100100101010")

    mAB.processAB("010")
    mAB.display_matrix()

    print("\nFinding closest\n")
    findm = MatrixOperations()
    findm.assign_word(5, "0100100100100000")
    findm.assign_word(3, "0110110110101010")
    findm.assign_word(7, "0100100100101010")

    findm.processAB("010")

    findm.assign_word(10, "0111111111111111")
    findm.assign_word(11, "0000000000000011")
    findm.assign_word(12, "0111011011011111")

    print("Bigger")
    print(findm.closest_find("0000000000000001", True))

    print("Smaller")
    print(findm.closest_find("0110110110101010", False))
