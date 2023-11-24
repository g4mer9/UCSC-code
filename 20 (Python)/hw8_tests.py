"""Test cases for hw8."""

import hw8

import unittest

class TestHomeworkEight(unittest.TestCase):

    def test_simple_evaluations(self):
        self.assertEqual(hw8.evaluate(10), 10)

        self.assertEqual(hw8.evaluate(["add", 10, 10]), 20)
        self.assertEqual(hw8.evaluate(["sub", 10, 10]), 0)
        self.assertEqual(hw8.evaluate(["mul", 10, 10]), 100)
        self.assertEqual(hw8.evaluate(["div", 10, 10]), 1)

        self.assertEqual(hw8.evaluate(["div", 11, 10]), 1)
        self.assertEqual(hw8.evaluate(["div", 200, 10]), 20)

        self.assertEqual(hw8.evaluate(["sub", 10, 100]), -90)

    def test_recursive_evaluations(self):
        nested1 = ["sub", ["add", ["div", ["mul", 20, 4], 2], 2], 0]
        self.assertEqual(hw8.evaluate(nested1), 42)

        nested2 = ["add", ["add", 1, 1],
                          ["add", 1, ["add", 1, 1]]]
        self.assertEqual(hw8.evaluate(nested2), 5)

        ## EAGER BEAVER STUDENTS: explain what this is doing and I will be
        ## impressed.
        expression = 1
        for i in range(8):
            expression = ["mul", 2, expression]
        self.assertEqual(hw8.evaluate(expression), 256)


    def test_dividing_by_zero(self):
        with self.assertRaises(ValueError):
            hw8.evaluate(["div", 10, ["sub", 5, 5]])

        with self.assertRaises(ValueError):
            hw8.evaluate(["div", 10, 0])


    def test_validate_good_bpps(self):
        self.assertTrue(hw8.validate(["div", 200, 10]))
        self.assertTrue(hw8.validate(["div", 10, ["sub", 5, 5]]))

        self.assertTrue(hw8.validate(
            ["add", ["add", 1, 1], ["add", 1, ["add", 1, 1]]]))
        self.assertTrue(hw8.validate(1))
        self.assertTrue(hw8.validate(
            ["mul", ["mul", 1, 1], ["mul", 1, ["mul", 1, 1]]]))


    def test_validate_bad_bpps(self):
        # some things that are not ints or lists
        with self.assertRaises(ValueError):
            hw8.validate("mul")
        with self.assertRaises(ValueError):
            hw8.validate(70.0)
        with self.assertRaises(ValueError):
            hw8.validate(("mul", 10, 15))

        # recursively contains a non-list
        with self.assertRaises(ValueError):
            hw8.validate(["mul", ("mul", 1, 4), 15])


        # wrong number of things in a list
        with self.assertRaises(ValueError):
            hw8.validate(["mul"])

        with self.assertRaises(ValueError):
            hw8.validate(["mul", 1])

        with self.assertRaises(ValueError):
            hw8.validate(["mul", 1, 2, 3])

        # undefined commands
        with self.assertRaises(ValueError):
            hw8.validate(["exp", 2, 8])

        with self.assertRaises(ValueError):
            hw8.validate(["send-email", 2, 8])

        # recursively contains an undefined command
        badexpression = ["exp", 2, 8]
        for i in range(8):
            badexpression = ["mul", badexpression, 2]
        with self.assertRaises(ValueError):
            hw8.validate(badexpression)


if __name__ == "__main__":
    unittest.main()
