#Riley Fink
#1895647
# (list any collaborators here: ...)
# The bimmypp programming language interpreter!

import json

def load_bimmypp(filename):
    with open(filename) as infile:
       return json.load(infile) 

def validate(bpp):
    """Returns True if this is a valid bimmypp program, or if it finds a
    problem, raises a ValueError."""

    # If we get passed an int, it's OK!
    if type(bpp) == int:
        return True
    #raise ValueError("ValueError exception thrown")

    # If it's a list, you must check...
    # Is it of length 3?
    # Assuming it's of length 3, is the first thing in the list one of
    # "add", "sub", "mul", or "div"?
    # If those aren't true, raise a ValueError.
    # Finally, you have to run validate (recursively) on the left operand and
    # right operand. (so things at index 1 and 2 in the list)
    # If it's anything else other than an int or a list, raise a ValueError.
    pass

def evaluate(bpp):
    """Evaluate a bpp expression. Returns the result of evaluating the program.
    Might also raise a ValueError, if we end up dividing by 0.
    """
    # If we get passed an int, then that's it! Just return the int value.
    # If we get passed a list, then we have to evaluate the expression.
    # Get the operator out of the list (at the 0 index).
    # RECURSIVELY EVALUATE the operands.
    # If the operator is "add", then add the two operands!
    # Likewise for sub and mul.
    # If we're doing division, we must check for 0.
    # If the right operator is 0, then raise a ValueError with the message
    # "divide by zero".
    # Assuming everything worked, return the result!
    pass

def run_bimmypp(filename):
    """Function for running a bimmypp program. Takes a filename and executes the file.

    You don't have to make any changes to this function."""
    try:
        bpp = load_bimmypp(filename)
    except json.decoder.JSONDecodeError:
        print("Could not load bimmypp file")
        return None
    except FileNotFoundError:
        print("no such file: ", filename)
        return None

    try:
        valid = validate(bpp)
    except ValueError as e:
        print(e)
        return None

    try:        
        value = evaluate(bpp)
        print("Success!")
        print("we got:", value)
        return value
    except ValueError as e:
        print(e)
        return None
