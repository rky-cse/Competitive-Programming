//https://cses.fi/paste/1c6ce2b91fae3887a7617e/
template <typename ArrayType, typename SegmentType>
class LazySegmentTree {
private:
    vector<SegmentType> sgt, lazy;
    int n_elements;
/****you should update this block according to requirements***************************/

    SegmentType identity_element=0;// change this if required
    SegmentType identity_update=0;// change this if required

    SegmentType merge(SegmentType a, SegmentType b) {
        return a + b; // Modify this for other operations (e.g., min, max)
        return min(a,b);
        return max(a,b);
    }
    void lazy_propagate(int v, int tl, int tr) {
        /*for sum */

        if (lazy[v] != identity_update) {
            sgt[v] += lazy[v] * (tr - tl + 1);
            if (tl != tr) { // Not a leaf node
                lazy[2 * v] += lazy[v];
                lazy[2 * v + 1] += lazy[v];
            }
            lazy[v] = identity_update;
        }

        /*for other op like min max*/

        // if (lazy[v] != identity_update) {
        //     sgt[v] =merge(lazy[v],sgt[v]);
        //     if (tl != tr) { // Not a leaf node
        //         lazy[2 * v] = merge(lazy[2*v],lazy[v]);
        //         lazy[2 * v + 1] = merge(lazy[2*v+1],lazy[v]);
        //     }
        //     lazy[v] = identity_update;
        // }
    }

    /********************************************************************************/

    void build(int v, int tl, int tr, const vector<ArrayType>& arr) {
        if (tl == tr) {
            sgt[v] = static_cast<SegmentType>(arr[tl]);  // Convert ArrayType to SegmentType
        } else {
            int tm = (tl + tr) / 2;
            build(2 * v, tl, tm, arr);
            build(2 * v + 1, tm + 1, tr, arr);
            sgt[v] = merge(sgt[2 * v], sgt[2 * v + 1]);
        }
    }

    

    SegmentType query(int v, int tl, int tr, int l, int r) {
        lazy_propagate(v, tl, tr);

        // If the query range [l, r] is outside the node range [tl, tr]
        if (tl > r || tr < l) return identity_element;
        
        // If the query range completely covers the node range
        if (l <= tl && tr <= r) return sgt[v];

        int tm = (tl + tr) / 2;
        return merge(query(2 * v, tl, tm, l, r),
                     query(2 * v + 1, tm + 1, tr, l, r));
    }

    void update_range(int v, int tl, int tr, int l, int r, SegmentType val) {
        lazy_propagate(v, tl, tr);

        // If the update range [l, r] is outside the node range [tl, tr]
        if (tl > r || tr < l) return;

        // If the update range completely covers the node range
        if (l <= tl && tr <= r) {
            lazy[v] = merge(lazy[v], val);
            lazy_propagate(v, tl, tr);
            return;
        }

        int tm = (tl + tr) / 2;
        update_range(2 * v, tl, tm, l, r, val);
        update_range(2 * v + 1, tm + 1, tr, l, r, val);
        sgt[v] = merge(sgt[2 * v], sgt[2 * v + 1]);
    }
    void update_point(int v, int tl, int tr, int pos, SegmentType new_value) {
        lazy_propagate(v, tl, tr);
        if (tl == tr) {
            sgt[v] = new_value;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update_point(2 * v, tl, tm, pos, new_value);
            } else {
                update_point(2 * v + 1, tm + 1, tr, pos, new_value);
            }
            sgt[v] = merge(sgt[2 * v], sgt[2 * v + 1]);
        }
    }

public:
    // Constructor with array to build the segment tree
    LazySegmentTree(const vector<ArrayType>& arr) 
        : n_elements(arr.size()) {
        sgt.resize(4 * n_elements, identity_element);
        lazy.resize(4 * n_elements, identity_update);
        build(1, 0, n_elements - 1, arr);
    }

    SegmentType query(int l, int r) {
        return query(1, 0, n_elements - 1, l, r);
    }

    void update_range(int l, int r, SegmentType addend) {
        update_range(1, 0, n_elements - 1, l, r, addend);
    }
    void update_point(int pos, SegmentType val) {
        update_point(1,0,n_elements-1,pos,val);
    }


};