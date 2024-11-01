

import java.util.*;
// State as stack

// <id, val>
class Pair {
    Identifier id;
    Value val;

    Pair (Identifier id, Value v) {
        this.id = id;
        this.val = v;
    }
}

class  State extends Stack<Pair> {
    public State( ) { }

    public State(Identifier id, Value val) {
        push(id, val);
    }

    // (1) Push function Implementation
    public State push(Identifier id, Value val) {
        // Push Implementation
        push(new Pair(id, val));
        return this;
    }

    // (2) Pop function Implementation (Optional)
    public Pair pop() {
        // Pop Implementation (Optional)
        return remove(size());
    }

    public Pair popByIndex(int index) {
        // Pop Implementation (Optional)
        return remove(index);
    }

    // (3) Lookup function Implementation
    public int lookup (Identifier v) {
        // Lookup Implementation
        for(int i=size()-1; i>=0; i--){
            if(this.get(i).id.equals(v)){
                return i;
            }
        }
        return -1;
    }

    // (4) Set Function Implementation
    public State set(Identifier id, Value val) {
        // Set Implementation
        int lookup = lookup(id);
        if (lookup >= 0)
            this.set(lookup, new Pair(id, val));
        else
            this.push(id, val);
        return this;
    }

    // (5) Get Function Implementation
    public Value get (Identifier id) {
        // Get Implementation
        int lookup = lookup(id);
        return this.get(lookup).val;
    }

}