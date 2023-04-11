// Parser.java
// Parser for language S

public class Parser {
    Token token;          // current token 
    Lexer lexer;
    String funId = "";

    public Parser(Lexer scan) { 
        lexer = scan;		  
        token = lexer.getToken(); // get the first token
    }
  
    private String match(Token t) {
        String value = token.value();
        if (token == t)
            token = lexer.getToken();
        else
            error(t);
        return value;
    }

    private void error(Token tok) {
        System.err.println("Syntax error: " + tok + " --> " + token);
        token=lexer.getToken();
    }
  
    private void error(String tok) {
        System.err.println("Syntax error: " + tok + " --> " + token);
        token=lexer.getToken();
    }
  
    public Command command() {
    // <command> ->  <decl> | <function> | <stmt>
	    if (isType()) {
	        Decl d = decl();
	        return d;
	    }
	
	   if (token == Token.FUN) {
	        Function f = function();
	        return f;
	    }
	
	    if (token != Token.EOF) {
	        Stmt s = stmt();
            return s;
	    }
	    return null;
    }


    
	private Decl decl() {
    // <decl>  -> <type> id [=<expr>]; <type> id[n]; 
        Type t = type();
	    String id = match(Token.ID);
	    Decl d = null;
	    if (token == Token.ASSIGN) {
	        match(Token.ASSIGN);
            Expr e = expr();
	        d = new Decl(id, t, e);
	    } else 
            d = new Decl(id, t);
	    if(token==Token.LBRACKET) {
	    	match(Token.LBRACKET);
	    	int n=literal().intValue();
	    	match(Token.RBRACKET);
	    	d=new Decl(id,t,n);
	    }
	    
	    match(Token.SEMICOLON);
	    return d;
    }

    private Decls decls () {
    // <decls> -> {<decl>}
        Decls ds = new Decls ();
	    while (isType()) {
	        Decl d = decl();
	        ds.add(d);
	    }
        return ds;             
    }

    private Function function() {
        // <function>  -> fun <type> id(<params>) <stmt> 
        match(Token.FUN);
    	Type t = type();
    	String str = match(Token.ID);
    	funId = str; 
    	Function f = new Function(str, t);
    	match(Token.LPAREN);
        if (token != Token.RPAREN)
        	f.params = params();
    	match(Token.RPAREN);
    	Stmt s = stmt();		
    	f.stmt = s;
    	    return f;
        }

        private Decls params() {
    	    Decls params = new Decls();
    	    Type t = type();
            String id = match(Token.ID);
    	    params.add(new Decl(id, t));
            while (token == Token.COMMA) {
    	        match(Token.COMMA);
    	        t = type();
                id = match(Token.ID);
                params.add(new Decl(id, t));
            }
            return params;
        }
        
    private Type type () {
    // <type>  ->  int | bool | void | string 
        Type t = null;
        switch (token) {
	    case INT:
            t = Type.INT; break;
        case BOOL:
            t = Type.BOOL; break;
        case VOID:
            t = Type.VOID; break;
        case STRING:
            t = Type.STRING; break;
        case ARRAY:
        	t = Type.ARRAY;break;
        default:
	        error("int | bool | void | string");
	    }
        match(token);
        return t;       
    }
  
    private Stmt stmt() {
    // <stmt> -> <block> | <assignment> | <ifStmt> | <whileStmt> | ...
        Stmt s = new Empty();
        switch (token) {
	    case SEMICOLON:
            match(token.SEMICOLON); return s;
        case LBRACE:			
	        match(Token.LBRACE);		
            s = stmts();
            match(Token.RBRACE);	
	        return s;
        case IF: 	// if statement 
            s = ifStmt(); return s;
        case WHILE:      // while statement 
            s = whileStmt(); return s;
        case ID:	// assignment
            s = assignment(); return s;
        case DO:
        	s=doStmt(); return s;
        case FOR:
        	s=forStmt();return s;
	    case LET:	// let statement 
            s = letStmt(); return s;
	    case READ:	// read statement 
            s = readStmt(); return s;
	    case PRINT:	// print statement 
            s = printStmt(); return s;
	    case ARRAY: // array statement
	    	s=assignment(); return s;
	    case RETURN: // return statement 
            s = returnStmt(); return s;
        default:  
	        error("Illegal stmt"); return null; 
	    }
    }
  
    private Stmts stmts () {
       // <block> -> {<stmt>}
        Stmts ss = new Stmts();
        while((token != Token.RBRACE) && (token != Token.END))
    	   ss.stmts.add(stmt()); 
        return ss;
     }
	
    private Let letStmt () {
    // <letStmt> -> let <decls> in <block> end
	    match(Token.LET);	
        Decls ds = decls();
	    match(Token.IN);
        Stmts ss = stmts();
        match(Token.END);
        match(Token.SEMICOLON);
        return new Let(ds,null, ss);
    }

    private Read readStmt() {
    // <readStmt> -> read id;
    	match(Token.READ);
    	String id = match(Token.ID);
    	match(Token.SEMICOLON);
    	return new Read(new Identifier(id));
    }
    
    private Return returnStmt() {
        // <returnStmt> -> return <expr>; 
            match(Token.RETURN);
            Expr e = expr();
            match(Token.SEMICOLON);
            return new Return(funId, e);
        }
    
    private Print printStmt() {
    // <printStmt> -> print <expr>;
    	match(Token.PRINT);
    	Expr expr = expr();
    	match(Token.SEMICOLON);
    	return new Print(expr);
    }

    private Stmt assignment() {
    // <assignment> -> id = <expr>;   
        Identifier id = new Identifier(match(Token.ID));
        if(token==Token.LBRACKET) {
        	// <array assignment> -> id[<expr>]=<expr>
			 match(Token.LBRACKET);
			 Expr e1 = expr();
			 match(Token.RBRACKET);
			 match(Token.ASSIGN);
			 Expr e2 = expr();
			 match(Token.SEMICOLON);
			 Array a=new Array(id,e1);
			 return new Assignment(a,e2);
        	}
        else if (token == Token.LPAREN)   // function call 
        	return call(id);
        
        match(Token.ASSIGN);
        Expr e = expr();
        match(Token.SEMICOLON);
        return new Assignment(id, e);
        
    }

    private Call call(Identifier id) {
        // <call> -> id(<expr>{,<expr>});
    	 match(Token.LPAREN);
    	 Exprs exprs = arguments();
    	 match(Token.RPAREN);
    	 return new Call(id,exprs);
       }
    
    private If ifStmt () {
    // <ifStmt> -> if (<expr>) then <stmt> [else <stmt>]
        match(Token.IF);
	    match(Token.LPAREN);
        Expr e = expr();
	    match(Token.RPAREN);
        match(Token.THEN);
        Stmt s1 = stmt();
        Stmt s2 = new Empty();
        if(token==Token.ELSE) {
        	match(Token.ELSE);
        	s2=stmt();
        }
        return new If(e,s1,s2);
    }

    private While whileStmt () {
    // <whileStmt> -> while (<expr>) <stmt>
    	match(Token.WHILE);
    	match(Token.LPAREN);
    	Expr e= expr();
    	match(Token.RPAREN);
    	Stmt s= stmt();
    	return new While(e,s);
    }
    private Stmts doStmt() {
    	// <doStmt> -> do <stmt> while (<expr>)
    	match(Token.DO);
    	Stmt s= stmt();
    	match(Token.WHILE);
    	match(Token.LPAREN);
    	Expr e = expr();
    	match(Token.RPAREN);
    	
    	// do-while
    	While wh = new While(e,s);
    	Stmts ss = new Stmts();
    	ss.stmts.add(s); ss.stmts.add(wh);
    	return ss;
    }
    private Let forStmt() {
    	// <forstmt> -> for(<type> id=<expr>; <expr>; id=<expr>)<stmt>
    	match(Token.FOR);
    	match(Token.LPAREN);
    	Type t = type();
    	String id1 = match(Token.ID);
        match(Token.ASSIGN);
        Expr e1 = expr();
        match(Token.SEMICOLON);
    	Expr con = expr();
    	match(Token.SEMICOLON);
    	String id2 = match(Token.ID);
        match(Token.ASSIGN);
        Expr e2 = expr();
    	match(Token.RPAREN);
    	Stmt s= stmt();
    	
    	// for문 
    	Decls ds= new Decls();
    	ds.add(new Decl(id1,t,e1));
       	
    	Stmts ss = new Stmts();
    	Assignment as=new Assignment(new Identifier(id2),e2);
    	ss.stmts.add(s); ss.stmts.add(as);
    	
    	Stmts sf = new Stmts();
    	While wh = new While(con,ss);
    	sf.stmts.add(wh);
    
    	return new Let(ds,null,sf);
    }

    private Expr expr () {
    // <expr> -> <bexp> {& <bexp> | '|'<bexp>} | !<expr> | true | false
        switch (token) {
	    case NOT:
	        Operator op = new Operator(match(token));
	        Expr e = expr();
            return new Unary(op, e);
        case TRUE:
            match(Token.TRUE);
            return new Value(true);
        case FALSE:
            match(Token.FALSE);
            return new Value(false);
      
	    default:
	    	Expr e1 = bexp();
	    	while(token==Token.AND || token==Token.OR) {
	    		Operator op1 = new Operator(match(token));
	    		Expr e2 = bexp();
	    		e1 = new Binary(op1,e1,e2);	
	    	}
	    	return e1;
	    }
}

    private Expr bexp() {
        // <bexp> -> <aexp> [ (< | <= | > | >= | == | !=) <aexp> ]
        Expr e = aexp();
        if(token==Token.LT || token==token.LTEQ || token==token.GT ||
    			token==Token.GTEQ || token==Token.EQUAL || token==Token.NOTEQ) {
    		Operator op = new Operator(match(token));
    		Expr e1=aexp();
    		e = new Binary(op,e,e1);
    	}
            return e;
        }
  
    private Expr aexp () {
        // <aexp> -> <term> { + <term> | - <term> }
        Expr e = term();
        while (token == Token.PLUS || token == Token.MINUS) {
            Operator op = new Operator(match(token));
            Expr t = term();
            e = new Binary(op, e, t);
        }
        return e;
    }
  
    private Expr term () {
        // <term> -> <factor> { * <factor> | / <factor>}
        Expr t = factor();
        while (token == Token.MULTIPLY || token == Token.DIVIDE) {
            Operator op = new Operator(match(token));
            Expr f = factor();
            t = new Binary(op, t, f);
        }
        return t;
    }
  
    private Expr factor() {
        // <factor> -> [-](id | <call> | literal | '('<aexp> ')')
        Operator op = null;
        if (token == Token.MINUS) 
            op = new Operator(match(Token.MINUS));

        Expr e = null;
        switch(token) {
        case ID:
            Identifier v = new Identifier(match(Token.ID));
            if(token==Token.LBRACKET) {
            	match(Token.LBRACKET);
            	Expr temp=expr();
            	match(Token.RBRACKET);
            	e=new Array(v,temp);
            	}
            else if (token == Token.LPAREN) {  // function call
                match(Token.LPAREN); 
                Call c = new Call(v,arguments());
                match(Token.RPAREN);
                e = c;
            } 
            else
            	e = v;
            break;
        case NUMBER: case STRLITERAL: 
            e = literal();
            break; 
        case LPAREN:
            match(Token.LPAREN); 
            e = expr();       
            match(Token.RPAREN);
            break; 
        default: 
            error("Identifier | Literal"); 
        }

        if (op != null)
            return new Unary(op, e);
        else return e;
    }
    
    private Exprs arguments() {
        // arguments -> [ <expr> {, <expr> } ]
            Exprs es = new Exprs();
            while (token != Token.RPAREN) {
                es.add(expr());
                if (token == Token.COMMA)
                    match(Token.COMMA);
                else if (token != Token.RPAREN)
                    error("Exprs");
            }  
            return es;  
        }
    
    private Value literal( ) {
        String s = null;
        switch (token) {
        case NUMBER:
            s = match(Token.NUMBER);
            return new Value(Integer.parseInt(s));
        case STRLITERAL:
            s = match(Token.STRLITERAL);
            return new Value(s);
        }
        throw new IllegalArgumentException( "no literal");
    }
 
    private boolean isType( ) {
        switch(token) {
        case INT: case BOOL: case STRING: 
            return true;
        default: 
            return false;
        }
    }
    
    public static void main(String args[]) {
	    Parser parser;
	    if (args.length == 0) {
            System.out.println("Begin parsing... ");
	        System.out.print(">> ");
	        Lexer.interactive = true;
	        parser  = new Parser(new Lexer());
	        do {
	            if (parser.token == Token.EOF) {
		            parser.token = parser.lexer.getToken();
		        }

		        Command command = null;
                try {
                    command = parser.command();
					if (command != null)
						command.display(0);
                } catch (Exception e) {
                    System.err.println(e);
                }
		        System.out.print("\n>> ");
	        } while(true);
	    }
    	else {
	        System.out.println("Begin parsing... " + args[0]);
	        parser  = new Parser(new Lexer(args[0]));
	        Command command = null;
	        do {
                try {
		            command = parser.command();
					if (command != null)
						command.display(0);
                } catch (Exception e) {
                    System.err.println(e);
                }
	        } while (command != null);
	    }
    } //main
} // Parser