import timeit

from texttable import Texttable

import exchangesort
import cases
import shellsort


def result_table_exchange():
    table = Texttable()
    table.add_row(['Length', 'Worst Case', 'Best Case', 'Average Case'])
    for term in [500, 1000, 2000, 4000, 8000]:
        start_wc = timeit.default_timer()
        wc = exchangesort.exchange_sort(cases.wc_exchange(term))
        end_wc = timeit.default_timer()
        start_bc = timeit.default_timer()
        bc = exchangesort.exchange_sort(cases.bc_exchange(term))
        end_bc = timeit.default_timer()
        start_ac = timeit.default_timer()
        ac = exchangesort.exchange_sort(cases.average_exchange(term))
        end_ac = timeit.default_timer()
        table.add_row([term, end_wc - start_wc,end_bc - start_bc,end_ac - start_ac])
    return table

def result_table_shell():
    table = Texttable()
    table.add_row(['Length', 'Worst Case', 'Best Case', 'Average Case'])
    for term in [500, 1000, 2000, 4000, 8000]:
        array,gaps = cases.wc_shell(term)
        start_wc = timeit.default_timer()
        wc = shellsort.shell_sort(array,gaps)
        end_wc = timeit.default_timer()
        start_bc = timeit.default_timer()
        bc = shellsort.shell_sort(cases.bc_exchange(term),cases.gaps_shell(term))
        end_bc = timeit.default_timer()
        start_ac = timeit.default_timer()
        ac = shellsort.shell_sort(cases.average_exchange(term),cases.gaps_shell(term))
        end_ac = timeit.default_timer()
        table.add_row([term, end_wc - start_wc,end_bc - start_bc,end_ac - start_ac])
    return table