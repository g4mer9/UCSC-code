def search_binary(list_of_words, target, debug_print=True):
    """ Find and return an index of target in list_of_words
    """
    # l and r represent the region of interest that we search over.
    # initially this is the whole of xs
    l = 0
    r = len(list_of_words)

    while l < r:
        m = (l + r) // 2  # The mid point of the interval
        if debug_print:
            print("Interval[{0}:{1}](size={2}), probed='{3}', target='{4}'"
                  .format(l, r, r - l, list_of_words[m], target))
        if target < list_of_words[m][0]:
            print("pain")
            r = m
        elif target > list_of_words[m][0]:
            print("pain2")
            l = m + 1
        else:
            assert target == list_of_words[m][0]
            return list_of_words[m][1]
    return -1