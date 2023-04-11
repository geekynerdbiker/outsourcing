// AST.java
// AST for S

import java.util.*;


class Indent{
}
abstract class Command {
    // Command = Decl | Function | Stmt
    Type type =Type.UNDEF;
	public void display(int level) { }
}

class Decls extends ArrayList<Decl> {
	 Decls() { super(); };
	    Decls(Decl d) {
		this.add(d);
	    }
    // Decls = Decl*
}

class Decl extends Command {
    // Decl = Type type; Identifier id 
    Identifier id;
    Expr expr = null;
    int arraysize=0;
    Decl (String s, Type t) {
        id = new Identifier(s); type = t;
    } // declaration 
    
    Decl (String s, Type t, int n) {
        id = new Identifier(s); type = t; arraysize = n;
    } // array declaration 
    
    Decl (String s, Type t, Expr e) {
        id = new Identifier(s); type = t; expr = e;
    } // declaration 
}

class Functions extends ArrayList<Function> {
    // Functions = Function*
	Functions() { super(); };
	    Functions(Function f) {
		this.add(f);
	  }
}

class Function extends Command  {
    // Function = Type type; Identifier id; Decls params; Stmt stmt
    Identifier id;
    Decls params;
    Stmt stmt;
   
    Function(String s, Type t) { 
        id = new Identifier(s); type = t; params = null; stmt = null;
    }

    public String toString ( ) { 
       return id.toString(); 
    } 
}

class Type {
    // Type = int | bool | string | void
    final static Type INT = new Type("int");
    final static Type BOOL = new Type("bool");
    final static Type STRING = new Type("string");
    final static Type VOID = new Type("void");
    final static Type FUN = new Type("fun");
    final static Type UNDEF = new Type("undefined");
    final static Type ERROR = new Type("error");
	final static Type ARRAY = new Type("array");
    
    protected String id;
    protected Type(String s) { id = s; }
    public String toString ( ) { return id; }
  
}

class ProtoType extends Type {
   // the type of a function and its parameters
   Type result;  
   Decls params;
   ProtoType (Type t, Decls ds) {
      super(t.id);
      result = t;
      params = ds;
   }
}

abstract class Stmt extends Command {
    // Stmt = Empty | Stmts | Assignment | If  | While | Let | Read | Print

}

class Empty extends Stmt {
}

class Stmts extends Stmt {
    // Stmts = Stmt*
    public ArrayList<Stmt> stmts = new ArrayList<Stmt>();
    Stmts() {
    	super(); 
        }

        Stmts(Stmt s) {
    	stmts.add(s);
        }
   
}

class For extends Stmt{}
class Do extends Stmt{}
class Assignment extends Stmt {
    // Assignment = Identifier id; Expr expr
    Identifier id=null;
    Array ar = null;
    Expr expr;

    Assignment (Identifier t, Expr e) {
        id = t;
        expr = e;
    }

    Assignment (Array a, Expr e) {      
        ar = a;
        expr = e;
    }

}

class If extends Stmt {
    // If = Expr expr; Stmt stmt1, stmt2;
    Expr expr;
    Stmt stmt1, stmt2;
    
    If (Expr t, Stmt tp) {
        expr = t; stmt1 = tp; stmt2 = new Empty( );
    }
    
    If (Expr t, Stmt tp, Stmt ep) {
        expr = t; stmt1 = tp; stmt2 = ep; 
    }
   
}


class While extends Stmt {
    // While = Expr expr; Stmt stmt;
    Expr expr;
    Stmt stmt;

    While (Expr t, Stmt b) {
        expr = t; stmt = b;
    }
  
}

class Let extends Stmt {
    // Let = Decls decls; Functions funs; Stmts stmts;
    Decls decls;
    Functions funs;
    Stmts stmts;

    Let(Decls ds, Functions fs, Stmts ss) {
        decls = ds;
        funs = fs;
        stmts = ss;
    }
   
}


class Read extends Stmt {
    // Read = Identifier id
    Identifier id;

    Read (Identifier v) {
        id = v;
    }
 
}

class Print extends Stmt {
    // Print =  Expr expr
    Expr expr;

    Print (Expr e) {
        expr = e;
    }
   
}

class Return extends Stmt {
    Identifier fid;
    Expr expr;

    Return (String s, Expr e) {
        fid = new Identifier(s);
        expr = e;
    }
   
}

class Try extends Stmt {
    // Try = Identifier id; Stmt stmt1; Stmt stmt2; 
    Identifier eid;
    Stmt stmt1; 
    Stmt stmt2; 

    Try(Identifier id, Stmt s1, Stmt s2) {
        eid = id; 
        stmt1 = s1;
        stmt2 = s2;
    }
}

class Raise extends Stmt {
    Identifier eid;

    Raise(Identifier id) {
        eid = id;
    }
}

class Exprs extends ArrayList<Expr> {
    // Exprs = Expr*
	
}

abstract class Expr extends Stmt {
    // Expr = Identifier | Value | Binary | Unary | Call
}

class Call extends Expr { 
    Identifier fid;  
    Exprs args;

    Call(Identifier id, Exprs a) {
       fid = id;
       args = a;
    }
}

class Identifier extends Expr {
    // Identifier = String id
    private String id;

    Identifier(String s) { id = s; }
    public String toString( ) { return id; }
    
    public boolean equals (Object obj) {
        String s = ((Identifier) obj).id;
        return id.equals(s);
    }
   
}
class Array extends Expr {
    // Array = Identifier id; Expr expr
    Identifier id;
    Expr expr = null;

    Array(Identifier s, Expr e) {id = s; expr = e;}

    public String toString( ) { return id.toString(); }
    
    public boolean equals (Object obj) {
        String s = ((Array) obj).id.toString();
        return id.equals(s);
    }
   
}

class Value extends Expr {
    // Value = int value | bool value | string value | function value
    protected boolean undef = true;
    Object value = null; Type type;
    
    Value(Type t) {
        type = t; 
        if (type == Type.INT) value = new Integer(0); 
        if (type == Type.BOOL) value = new Boolean(false); 
        if (type == Type.STRING) value = ""; 
        if(type== Type.ARRAY) value=new Array(null,null);
        undef = false;
    }

    Value(Object v) {
        if (v instanceof Integer) type = Type.INT;
        if (v instanceof Boolean) type = Type.BOOL;
        if (v instanceof String) type = Type.STRING;
        if (v instanceof Function) type = Type.FUN;
        if (v instanceof Value[]) type = Type.ARRAY;
        value = v; undef = false; 
    }

    Object value() { return value; }

    int intValue( ) { 
        if (value instanceof Integer )
        	return ((Integer) value).intValue();
      
        return 0; 
    }
    
    boolean boolValue( ) { 
        if (value instanceof Boolean) 
            return ((Boolean) value).booleanValue(); 
      
        return false; 
    } 

    String stringValue ( ) {
        if (value instanceof String) 
            return (String) value; 
     
        return "";
    }

    Function funValue ( ) {
        if (value instanceof Function) {
            return (Function) value; 
        }
        return null; 
    }

    Value[] arrValue ( ) {
        if (value instanceof Value[]) {
            return (Value[]) value; 
        }
        else return null;
    }
    
    Type type ( ) { return type; }

    public String toString( ) {
        if (type == Type.INT) return "" + intValue(); 
        if (type == Type.BOOL) return "" + boolValue();
        if (type == Type.STRING) return "" + stringValue();
        if (type == Type.FUN) return "" + funValue();
        if (type == Type.ARRAY) return "" + arrValue();
        return "undef";
    }
    
    
}

class Binary extends Expr {
// Binary = Operator op; Expr expr1; Expr expr2;
    Operator op;
    Expr expr1, expr2;

    Binary (Operator o, Expr e1, Expr e2) {
        op = o; expr1 = e1; expr2 = e2;
    } // binary
    
   
}

class Unary extends Expr {
    // Unary = Operator op; Expr expr
    Operator op;
    Expr expr;

    Unary (Operator o, Expr e) {
        op = o; 
        expr = e;
    } // unary
   
}

class Operator {
    String val;
    
    Operator (String s) { 
	    val = s; 
    }
	public String toString( ) { 
	    return val; 
    }

    public boolean equals(Object obj) { 
	    return val.equals(obj); 
    }
   
}