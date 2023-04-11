// Sint.java
// Interpreter for S
import java.util.Iterator;
import java.util.Scanner;

public class Sint {
    static Scanner sc = new Scanner(System.in);
    static State state = new State();

    State Eval(Command c, State state) { 
	if (c instanceof Decl) {
	    Decls decls = new Decls();
	    decls.add((Decl) c);
	    return allocate(decls, state);
	}
	
	if (c instanceof Function) {
	    Function f = (Function) c; 
	    state.push(f.id, new Value(f)); 
	    return state;
	}

	
	if (c instanceof Stmt)
	    return Eval((Stmt) c, state); 
		
	    throw new IllegalArgumentException("no command");
    }
  
    State Eval(Stmt s, State state) {
        if (s instanceof Empty) 
	        return Eval((Empty)s, state);
        if (s instanceof Assignment)  
	        return Eval((Assignment)s, state);
        if (s instanceof If)  
	        return Eval((If)s, state);
        if (s instanceof While)  
	        return Eval((While)s, state);
        if (s instanceof Stmts)  
	        return Eval((Stmts)s, state);
	    if (s instanceof Let)  
	        return Eval((Let)s, state);
	    if (s instanceof Read)  
	        return Eval((Read)s, state);
	    if (s instanceof Print)  
	        return Eval((Print)s, state);
        if (s instanceof Call) 
	        return Eval((Call)s, state);
	    if (s instanceof Return) 
	        return Eval((Return)s, state);
	    if (s instanceof Array)
	    	return Eval((Array)s, state);
        throw new IllegalArgumentException("no statement");
    }
    
    // call without return value
    State Eval(Call c, State state) {
    	 Value v = state.get(c.fid);  		// find function
         Function f = v.funValue();
         State s = newFrame(state, c, f); // create new frame on the stack
         s = Eval(f.stmt, s); 					// interpret the call
         s.pop();
         s = deleteFrame(s, c, f); 		// delete the frame on the stack
         return s;
    }

    // value-returning call 
    Value V (Call c, State state) {
	    Value v = state.get(c.fid);  		// find function
        Function f = v.funValue();
        State s = newFrame(state, c, f); // create new frame on the stack
        s = Eval(f.stmt, s); 					// interpret the call
        v = s.pop().val;   						// remove the return value
        s = deleteFrame(s, c, f); 			// delete the frame on the stack
    	return v;
    }

    State Eval(Return r, State state) {
        Value v = V(r.expr, state);
        return state.push(r.fid, v);
    }

    State newFrame (State state, Call c, Function f) {
        if (c.args.size() == 0) 
            return state;
        Value val[]=new Value[f.params.size()];
        int i=0;
        for(Expr e : c.args)
        	val[i++]=V(e,state);
        // 현재 상태에서 매개 변수 기억공간 할당 
        State s = allocate(f.params,state);
        // 인자의 값을 매개변수에 전달 
        Iterator<Decl> it = f.params.iterator();
        for(int j=0;j<f.params.size();j++) {
	        state.set(it.next().id, new Value(val[j]));
        }
	    return s;
    }

    State deleteFrame (State state, Call c, Function f) {
    	// 상태로부터 매개변수를 위한 기억공간 제거 
    	return free(f.params, state);
    }
    
    
    State Eval(Empty s, State state) {
        return state;
    }
  
    State Eval(Assignment a, State state) {
    	if(a.ar!=null) {
    		Array arr = a.ar;
    		Expr e = arr.id;
    		int i;
    		if(arr.expr instanceof Array) {
    			Array i_a = (Array)arr.expr;
    			i=V(i_a,state).intValue();
    		}
    		
    		else {
    			i = V(arr.expr,state).intValue();
    		}
    		Value v[]=state.get(arr.id).arrValue();	
    		v[i]=V(a.expr,state);
    		return state;
    	}
        Value v = V(a.expr, state);
        State s=state.set(a.id, v);
        	return s;
    }
    State Eval(Read r, State state) {
    	Type t;
    	if(state.get(r.id).value() instanceof Value) {
    		t=((Value)state.get(r.id).value()).type();
    	}
    	else {
    		t=(state.get(r.id)).type();
    	}
   	 	if (t==Type.INT) {
	        int i = sc.nextInt();
	        state.set(r.id, new Value(i));
	    } 

	    if (t == Type.BOOL) {
	        boolean b = sc.nextBoolean();	
          state.set(r.id, new Value(b));
	    }
	    
	   if (t == Type.STRING) {
	        String s = sc.nextLine();	
	        state.set(r.id, new Value(s));
	    }
	/*
        if (r.id.type == Type.INT) {
	        int i = sc.nextInt();
	        state.set(r.id, new Value(i));
	    } 

	    if (r.id.type == Type.BOOL) {
	        boolean b = sc.nextBoolean();	
            state.set(r.id, new Value(b));
	    }

	//
	// input string 
	*/
	    return state;
    }

    State Eval(Print p, State state) {
	    System.out.println(V(p.expr, state).value());
        return state; 
    }
  
    State Eval(Stmts ss, State state) {
        for (Stmt s : ss.stmts) {
            state = Eval(s, state);
        }
        return state;
    }
  
    State Eval(If c, State state) {
        if (V(c.expr, state).boolValue( ))
            return Eval(c.stmt1, state);
        else
            return Eval(c.stmt2, state);
    }
 
    State Eval(While l, State state) {
        if (V(l.expr, state).boolValue( ))
            return Eval(l, Eval(l.stmt, state));
        else 
	        return state;
    }

    State Eval(Let l, State state) {
        State s = allocate(l.decls, state);
        s = Eval(l.stmts,s);
	    return free(l.decls, s);
    }

    State allocate (Decls ds, State state) {
   	 if (ds != null) {
	    	Iterator iterator = ds.iterator();
			while(iterator.hasNext()) {
				Decl d = (Decl)iterator.next();
				if(d.expr==null ) {
					if(d.type == Type.INT) {
						state.push(d.id,new Value(0));
					}
					if(d.type == Type.BOOL) {
						state.push(d.id,new Value(false));
					
					}if(d.type==Type.STRING) {
						state.push(d.id,new Value(""));
					}
					// Array
					if(d.arraysize!=0) {
						int n = d.arraysize;
						Value[] value = new Value[n];
						state.push(d.id,new Value(value));
						}
					}
				else {
					state.push(d.id,new Value(d.expr));
				}
			}	
			return state;
   	 }
       return null;
    }

    State free (Decls ds, State state) {
    	   if (ds != null) {
    		Iterator iterator = ds.iterator();
   			while(iterator.hasNext()) {
   	    		Decl d = (Decl)iterator.next();
   	    		state.pop();
   	    	}
   			return state;
   	    }
   	    return null;
    }

    Value binaryOperation(Operator op, Value v1, Value v2) {
    	check(!v1.undef && !v2.undef,"reference to undef value");
    	if(v1.value instanceof Value) {
            v1=((Value)((Value) v1).value());
    	}
    	if(v2.value instanceof Value) {
            v2=((Value)((Value) v2).value());
    	}
    	switch (op.val) {
	    case "+":
            return new Value(v1.intValue() +v2.intValue());
        case "-": 
            return new Value(v1.intValue() - v2.intValue());
        case "*": 
            return new Value(v1.intValue() * v2.intValue());
        case "/": 
            return new Value(v1.intValue() / v2.intValue());
	
	// relational operations 
        case "==":
        	if(v1.type()==Type.INT && v2.type()==Type.INT) {
        		return new Value(v1.intValue()==v2.intValue());
        	}
        	return new Value(v1.stringValue().equals(v2.stringValue()));
        case "!=":
        	if(v1.type()==Type.INT && v2.type()==Type.INT) {
        		return new Value(v1.intValue()!=v2.intValue());
        	}
        	return new Value(!v1.stringValue().equals(v2.stringValue()));
        case "<":
        	if(v1.type()==Type.INT && v2.type()==Type.INT) {
        		return new Value(v1.intValue()<v2.intValue());
        	}
        	return new Value(v1.stringValue().compareTo(v2.stringValue())<0 ?true: false);
        case ">":
        	if(v1.type()==Type.INT && v2.type()==Type.INT) {
        		return new Value(v1.intValue()>v2.intValue());
        	}
        	return new Value(v1.stringValue().compareTo(v2.stringValue())>0 ?true: false);
        case "<=":
        	if(v1.type()==Type.INT && v2.type()==Type.INT) {
        		return new Value(v1.intValue()<=v2.intValue());
        	}
        	return new Value(v1.stringValue().compareTo(v2.stringValue())<=0 ?true: false);
        case ">=":
        	if(v1.type()==Type.INT && v2.type()==Type.INT) {
        		return new Value(v1.intValue()>=v2.intValue());
        	}
        	return new Value(v1.stringValue().compareTo(v2.stringValue())>=0 ?true: false);
	
      // logical operations
        case "&":
        	return new Value(v1.boolValue()&v2.boolValue());
        case "|":
        	return new Value(v1.boolValue()|v2.boolValue());
	    default:
	        throw new IllegalArgumentException("no operation");
	    }
    } 
    
    Value unaryOperation(Operator op, Value v) {
        check( !v.undef, "reference to undef value");
	    switch (op.val) {
        case "!": 
            return new Value(!v.boolValue( ));
        case "-": 
            return new Value(-v.intValue( ));
        default:
            throw new IllegalArgumentException("no operation: " + op.val); 
        }
    } 

    static void check(boolean test, String msg) {
        if (test) return;
        System.err.println(msg);
    }

    Value V(Expr e, State state) {
        if (e instanceof Value) {
            return (Value) e;
        }
        if (e instanceof Identifier) {
	        Identifier v = (Identifier) e;
	        if(state.get(v).value() instanceof Value) {
	    		return ((Value)state.get(v).value());
	    	}
            return (Value)(state.get(v));
	    }
        if (e instanceof Array) {
        	Identifier v =((Array) e).id;
        	Expr ex = ((Array) e).expr;
        	int i;
        	
        	if(ex instanceof Identifier) {
        		Identifier v1 = (Identifier)ex;
        		i = Integer.parseInt(state.get(v1).value().toString());
        	}
        	
        	else {
        		if(ex instanceof Array) {
        			Array i_a = (Array)ex;
        			i=V(i_a,state).intValue();
            	}
        		
        		else {
        			/*i =Integer.parseInt(new Value(ex).value().toString());
        			*/i = Integer.parseInt(""+V(ex,state));
        		}
        	}
        	Value[]arr_v = state.get(v).arrValue();
    		return (Value)(arr_v[i]);
        }
        if (e instanceof Binary) {
            Binary b = (Binary) e;
            Value v1 = V(b.expr1, state);
            Value v2 = V(b.expr2, state);
            return binaryOperation (b.op, v1, v2); 
        }

        if (e instanceof Unary) {
            Unary u = (Unary) e;
            Value v = V(u.expr, state);
            return unaryOperation(u.op, v); 
        }

        if (e instanceof Call) 
    	    return V((Call)e, state);  
        throw new IllegalArgumentException("no operation");
    }

    public static void main(String args[]) {
	    if (args.length == 0) {
	        Sint sint = new Sint(); Lexer.interactive = true;
            System.out.println("Language S Interpreter 1.0");
            System.out.print(">> ");
	        Parser parser  = new Parser(new Lexer());

	        do { // Program = Command*
	            if (parser.token == Token.EOF)
		        parser.token = parser.lexer.getToken();
	       
	            Command command=null;
                try {
	                command = parser.command();
	                if (command != null)
						command.display(0);
                   // command.type = TypeChecker.Check(command); 
                } catch (Exception e) {
                    System.out.println(e);
		            System.out.println(">> ");
                    continue;
                }

	            if (command.type != Type.ERROR) {
                    System.out.println("\nInterpreting..." );
                    try {
                        state = sint.Eval(command, state);
                    } catch (Exception e) {
                         System.err.println(e);  
                    }
                }
		    System.out.print(">> ");
	        } while (true);
	    }
        else {
	        System.out.println("Begin parsing... " + args[0]);
	        Command command = null;
	        Parser parser  = new Parser(new Lexer(args[0]));
	        Sint sint = new Sint();

	        do {	// Program = Command*
	            if (parser.token == Token.EOF)
                    break;

                try {
		            command = parser.command();
		            if (command != null)
						command.display(0);
                    // command.type = TypeChecker.Check(command);    
                } catch (Exception e) {
                    System.out.println(e);
                    continue;
                }

	            if (command.type!=Type.ERROR) {
                    System.out.println("\nInterpreting..." + args[0]);
                    try {
                        state = sint.Eval(command, state);
                    } catch (Exception e) {
                        System.err.println(e);  
                    }
                }
	        } while (command != null);
        }        
    }
}