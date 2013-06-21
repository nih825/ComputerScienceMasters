public class TTTClient{

    TicTacToe game;
    static final byte MARK_X = 0;
    static final byte MARK_O = 1;
    byte currentMove;
    boolean winner = false;

    public TTTClient(TicTacToe game){
	this.game = game;
	currentMove = MARK_X;
    }

    public void go(){
	String input, action;
	String[] tokens;


	while (true){
	    System.out.print("TTT > ");
	    input = ParserUtils.getKeyInput();
	    tokens = ParserUtils.getTokens(input);
	    action = tokens[0];
	    
	    if (action.equalsIgnoreCase("restart")){
		game.reset();
		continue;
	    }

	    if (action.equalsIgnoreCase("exit"))
		break;

	    else if (action.equalsIgnoreCase("move")){
		byte row, col;
		try{
		    col = Byte.parseByte(tokens[1]);
		    row = Byte.parseByte(tokens[2]);
		}
		catch(Exception e){
		    System.out.println(e.getMessage());
		    System.out.println("usage: move row col");
		    continue;
		}
		boolean verify = game.placeMark(col,row,currentMove);
		if (!verify){
		    System.out.println("error moving, try again");
		}
		else{
		    winner = game.checkWinner();
		    if (winner){
			System.out.println("WINNING MOVE: game over");
			game.showBoard();
			game.reset();
		    }
		    else{
			switchMoves();
		    }
		}
		
	    }

	    else if (action.equalsIgnoreCase("show")){
		game.showBoard();
	    }
	    
	    else {
		System.out.println("invalid command");
		continue;
	    }

	}
	
    }
    
    private void switchMoves(){
	if (currentMove == MARK_X)
	    currentMove = MARK_O;
	else if (currentMove == MARK_O)
	    currentMove = MARK_X;
    }


    public static void main(String[] args){
	TicTacToe game = new TicTacToe();
	TTTClient client = new TTTClient(game);
	client.go();
    }

}
