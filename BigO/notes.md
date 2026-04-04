# Big O
How time scales with respect to some input variables

1. Different steps get added
    function something() {
        doStep1(); // O(a)
        doStep2(); // O(b)
    }              // O(a + b)
2. Drop constants 
    function minMax1(array) {
        min, max = null
        foreach e in array { O(n)
            min = MIN(e, min)
        }
        foreach e in array { // O(n)
            max = MAX(e, max)
        }
    } // And are O(n) we don't use O(2n) we are just looking for linearity, looking for quadratics
3. Different inputs =? different variables 
    int intersectionSize(arrayA, arrayB) {
        int count = 0
        for a in arrayA {
            for b in arrayB {
                if a == b {
                    cont = cont + 1
                }
            }
        }
        return count
    } // The first thought is to declare the complexity as O(n^2), but what means n? the size of which array?
      // The correct is O(a * b) a = length of arrayA, b = length of arrayB   
4. Drop non-dominate terms
    function doThis(array) {
        max = null
        foreach a in array { // O(n)
            max = MAX(a, max)
        }
        print max
        foreach a in array {
            foreach b in array { // O(n^2)
                print a, b
            }
        } // O(nˆ2) <= O(n + n^2) <= O (nˆ2 + nˆ2 ) // If left and right are equivalent (see rule 2), then center is too
    } O(n + nˆ2) => O(nˆ2) the nˆ2 say the way the time complexity will change
