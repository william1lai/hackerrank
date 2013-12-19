#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>

using namespace std;

struct Piece
{
	int r;
	int c;
	bool color;
};

struct Move
{
	int r0;
	int c0;
	int rf;
	int cf;
};

struct Board
{
	vector<string> board;
	bool turn;
};

struct MoveScore
{
	Move m;
	int score;
};

vector<Move> generateMoves(Board b)
{
	vector<Move> allmvs;
	bool turn = b.turn;
	char p = 'b';
	char other = 'w';
	int rdir = 1;
	if (turn)
	{
		other = 'b';
		p = 'w';
		rdir = -1;
	}	
	
	for (int r = 0; r < 8; r++)
	for (int c = 0; c < 8; c++)
	{
		if (b.board[r][c] == p || b.board[r][c] == toupper(p))
		{
			int rf = r + rdir;
			if (rf >= 0 && rf < 8) //move forwards
			{
				if (c + 1 < 8)
				{
					char dest = b.board[rf][c+1];
					if (dest == '_')
					{
						Move m;
						m.r0 = r; m.c0 = c; m.rf = rf; m.cf = c + 1;
						allmvs.push_back(m);
					}
					else if (tolower(dest) == other) //capture
					{
						int rcapt = rf + rdir;
						if (rcapt >= 0 && rcapt < 8)
						{
							if (c + 2 < 8)
							{
								if (b.board[rcapt][c+2] == '_')
								{
									Move m;
									m.r0 = r; m.c0 = c; m.rf = rcapt; m.cf = c + 2;
									allmvs.push_back(m);
								}
							}
						}
					}
				}
				if (c - 1 >= 0)
				{
					char dest = b.board[rf][c-1];
					if (dest == '_')
					{
						Move m;
						m.r0 = r; m.c0 = c; m.rf = rf; m.cf = c - 1;
						allmvs.push_back(m);
					}
					else if (tolower(dest) == other) //capture
					{
						int rcapt = rf + rdir;
						if (rcapt >= 0 && rcapt < 8)
						{
							if (c - 2 >= 0)
							{
								if (b.board[rcapt][c-2] == '_')
								{
									Move m;
									m.r0 = r; m.c0 = c; m.rf = rcapt; m.cf = c - 2;
									allmvs.push_back(m);
								}
							}
						}
					}
				}
			}
			
			int rrf = r - rdir;
			if (b.board[r][c] == toupper(p))
			{
				if (rrf >= 0 && rrf < 8) //move backwards if king
				{
					if (c + 1 < 8)
					{
						char dest = b.board[rrf][c+1];
						if (dest == '_')
						{
							Move m;
							m.r0 = r; m.c0 = c; m.rf = rrf; m.cf = c + 1;
							allmvs.push_back(m);
						}
						else if (tolower(dest) == other) //capture
						{
							int rcapt = rrf - rdir;
							if (rcapt >= 0 && rcapt < 8)
							{
								if (c + 2 < 8)
								{
									if (b.board[rcapt][c+2] == '_')
									{
										Move m;
										m.r0 = r; m.c0 = c; m.rf = rcapt; m.cf = c + 2;
										allmvs.push_back(m);
									}
								}
							}
						}
					}
					if (c - 1 >= 0)
					{
						char dest = b.board[rrf][c-1];
						if (dest == '_')
						{
							Move m;
							m.r0 = r; m.c0 = c; m.rf = rrf; m.cf = c - 1;
							allmvs.push_back(m);
						}
						else if (tolower(dest) == other) //capture
						{
							int rcapt = rrf - rdir;
							if (rcapt >= 0 && rcapt < 8)
							{
								if (c - 2 >= 0)
								{
									if (b.board[rcapt][c-2] == '_')
									{
										Move m;
										m.r0 = r; m.c0 = c; m.rf = rcapt; m.cf = c - 2;
										allmvs.push_back(m);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	vector<Move> captures;
	for (Move m : allmvs)
		if (abs(m.rf - m.r0) == 2)
			captures.push_back(m);
	
	if (captures.size() > 0)
		return captures;	
	return allmvs;
}

Board makeMove(Board b, Move m)
{
	bool capture = abs(m.rf - m.r0) == 2;
	b.board[m.rf][m.cf] = b.board[m.r0][m.c0];
	if (!b.turn)
	{
		if (m.rf == 7)
			b.board[m.rf][m.cf] = 'B';
	}
	else
	{
		if (m.rf == 0)
			b.board[m.rf][m.cf] = 'W';
	}
	b.board[m.r0][m.c0] = '_';
	
	if (capture)
	{
		b.board[(m.rf + m.r0)/2][(m.cf + m.c0)/2] = '_';
	}
	return b;
}

int staticEval(Board b)
{
	int score = 0;
	char p = 'b';
	char other = 'w';
	int rdir = -1;
	int home = 0;
	int oks = 500;
	int os = 300;
	int tks = 500;
	int ts = 300;	
	if (b.turn)
	{
		p = 'w';
		rdir = 1;
		other = 'b';
		home = 7;
	}

	int rcount = 0;
	int tcount = 0;
	for (int r = 0; r < 8; r++)
	for (int c = 0; c < 8; c++)
	{
		if (tolower(b.board[r][c]) == p)
			rcount++;
		else if (tolower(b.board[r][c]) == other)
			tcount++;
	}

	int setting = 0; //0 is normal, 1 is aggressive endgame, 2 is passive endgame
	if (rcount > tcount && tcount < 3)
		setting = 1;
	else if (tcount > rcount && rcount < 3)
		setting = 2;
	
	for (int r = 0; r < 8; r++)
	for (int c = 0; c < 8; c++)
	{
		bool front2 = ((r - rdir*2) >= 0) && ((r - rdir*2) < 8);
		bool behind2 = ((r + rdir*2) >= 0) && ((r + rdir*2) < 8);
		bool left2 = (c - 2 >= 0);
		bool right2 = (c + 2 < 8);

		if (b.board[r][c] == toupper(p))
		{
			score = score + oks;
		}
		else if (b.board[r][c] == toupper(other))
		{
			score = score - tks;
			if (setting == 1)
			{
				if (front2)
				{
					if (left2 && tolower(b.board[r - rdir*2][c - 2]) == p)
						score = score + 40;
					if (right2 && tolower(b.board[r - rdir*2][c + 2]) == p)
						score = score + 40;
					if (tolower(b.board[r - rdir*2][c]) == p)
						score = score + 40;
				}
				if (behind2)
				{
					if (left2 && b.board[r + rdir*2][c - 2] == toupper(p))
						score = score + 30;
					if (right2 && b.board[r + rdir*2][c + 2] == toupper(p))
						score = score + 30;
					if (b.board[r + rdir*2][c] == toupper(p))
						score = score + 30;
				}
				if (left2 && b.board[r][c-2] == toupper(p))
					score = score + 30;
				if (right2 && b.board[r][c+2] == toupper(p))
					score = score + 30;
			}				
		}
		else if (b.board[r][c] == p)
		{
			if (!b.turn && c == 0)
				score++; //small adjustment to try to force opening towards edge
			score = score + os - (home-r)*(home-r);
		}
		else if (b.board[r][c] == other)
		{
			score = score - ts + (7-home-r)*(7-home-r);
			if (setting == 1)
			{
				if (front2)
				{
					if (left2 && tolower(b.board[r - rdir*2][c - 2]) == p)
						score = score + 40;
					if (right2 && tolower(b.board[r - rdir*2][c + 2]) == p)
						score = score + 40;
					if (tolower(b.board[r - rdir*2][c]) == p)
						score = score + 40;
				}
				if (behind2)
				{
					if (left2 && b.board[r + rdir*2][c - 2] == toupper(p))
						score = score + 30;
					if (right2 && b.board[r + rdir*2][c + 2] == toupper(p))
						score = score + 30;
					if (b.board[r + rdir*2][c] == toupper(p))
						score = score + 30;
				}
				if (left2 && tolower(b.board[r][c-2]) == p)
					score = score + 30;
				if (right2 && tolower(b.board[r][c+2]) == p)
					score = score + 30;
			}	
		}
		else //'_'
		{
			if (r - 1 >= 0)
			{
				if (c - 1 >= 0)
				{
					char cc = b.board[r-1][c-1];
					if (cc == 'b' || cc == 'B' || cc == 'W')
						score = score + 20*(p == tolower(cc)) - 20*(other == tolower(cc));
				}
				if (c + 1 < 8)
				{
					char cc = b.board[r-1][c+1];
					if (cc == 'b' || cc == 'B' || cc == 'W')
						score = score + 20*(p == tolower(cc)) - 20*(other == tolower(cc));
				}
			}
			if (r + 1 < 8)
			{
				if (c - 1 >= 0)
				{
					char cc = b.board[r+1][c-1];
					if (cc == 'w' || cc == 'W' || cc == 'B')
						score = score + 20*(p == tolower(cc)) - 20*(other == tolower(cc));
				}
				if (c + 1 < 8)
				{
					char cc = b.board[r+1][c+1];
					if (cc == 'w' || cc == 'W' || cc == 'B')
						score = score + 20*(p == tolower(cc)) - 20*(other == tolower(cc));
				}
			}
		}
				
	}
	return score;
}

MoveScore alphabetaMin(Board b, MoveScore alpha, MoveScore beta, int depth);

MoveScore alphabetaMax(Board b, MoveScore alpha, MoveScore beta, int depth)
{
	if (depth == 0)
	{
		vector<Move> mvs = generateMoves(b);
		if (mvs.size() > 0 && (mvs[0].rf - mvs[0].r0) == 2)
		{
			Board temp = makeMove(b, mvs[0]);
			int last = mvs[0].rf*10 + mvs[0].cf;
			bool capt = true;
			while (capt)
			{
				vector<Move> moremvs = generateMoves(temp);
				capt = false;
				if (moremvs.size() == 0 || abs(moremvs[0].rf - moremvs[0].r0) != 2)
					break;
				for (Move mm : moremvs)
				{
					if (mm.r0*10 + mm.c0 == last)
					{
						temp = makeMove(temp, mm);
						last = mm.rf*10 + mm.cf;
						capt = true;
						break;
					}
				}
			}
			temp.turn = !temp.turn;
        	        return alphabetaMin(temp, alpha, beta, 0);
		}

		MoveScore ms;
		ms.m = alpha.m;
		ms.score = staticEval(b);
		return ms;
	}
               
        int score;
        vector<Move> mvs = generateMoves(b);
        for (Move m : mvs)
        {
        	Board temp = b;
                temp = makeMove(temp, m);
		int last = m.rf*10 + m.cf;
		bool capt = abs(m.rf - m.r0) == 2;
		while (capt)
		{
			vector<Move> moremvs = generateMoves(temp);
			capt = false;
			if (moremvs.size() == 0 || abs(moremvs[0].rf - moremvs[0].r0) != 2)
				break;
			for (Move mm : moremvs)
			{
				if (mm.r0*10 + mm.c0 == last)
				{
					temp = makeMove(temp, mm);
					last = mm.rf*10 + mm.cf;
					//cerr << "Max Double hop at " << (mm.rf*10 + mm.cf) << "\n";
					capt = true;
					break;
				}
			}
		}

		temp.turn = !temp.turn;
                MoveScore ms = alphabetaMin(temp, alpha, beta, depth - 1);
                ms.m = m;
                score = ms.score;

                if (score >= beta.score)
                	return beta; //fail hard beta-cutoff
                if (score > alpha.score)
                	alpha = ms;
        }
	return alpha;
}
        
MoveScore alphabetaMin(Board b, MoveScore alpha, MoveScore beta, int depth)
{
	if (depth == 0)
	{
		vector<Move> mvs = generateMoves(b);
		if (mvs.size() > 0 && (mvs[0].rf - mvs[0].r0) == 2)
		{
			Board temp = makeMove(b, mvs[0]);
			int last = mvs[0].rf*10 + mvs[0].cf;
			bool capt = true;
			while (capt)
			{
				vector<Move> moremvs = generateMoves(temp);
				capt = false;
				if (moremvs.size() == 0 || abs(moremvs[0].rf - moremvs[0].r0) != 2)
					break;
				for (Move mm : moremvs)
				{
					if (mm.r0*10 + mm.c0 == last)
					{
						temp = makeMove(temp, mm);
						last = mm.rf*10 + mm.cf;
						capt = true;
						break;
					}
				}
			}
			temp.turn = !temp.turn;
        	        return alphabetaMax(temp, alpha, beta, 0);
		}

		MoveScore ms;
		ms.m = alpha.m;
		ms.score = -staticEval(b);
		return ms;
	}
				
        int score;
        for (Move m : generateMoves(b))
        {
        	Board temp = b;
                temp = makeMove(temp, m);
		int last = m.rf*10 + m.cf;
		bool capt = abs(m.rf - m.r0) == 2;
		while (capt)
		{
			vector<Move> moremvs = generateMoves(temp);
			capt = false;
			if (moremvs.size() == 0 || abs(moremvs[0].rf - moremvs[0].r0) != 2)
				break;
			for (Move mm : moremvs)
			{
				if (mm.r0*10 + mm.c0 == last)
				{
					temp = makeMove(temp, mm);
					last = mm.rf*10 + mm.cf;
					//cerr << "Min Double hop at " << (mm.rf*10 + mm.cf) << "\n";
					capt = true;
					break;
				}
			}
		}

		temp.turn = !temp.turn;
                MoveScore ms = alphabetaMax(temp, alpha, beta, depth - 1);
                ms.m = m;
                score = ms.score;
                if (score <= alpha.score)
                {
                        return alpha; //fail hard alpha-cutoff
                }
        	if (score < beta.score)
        		beta = ms;
        }
	return beta;
}
		
Move evaluate(Board b, int depth)
{
	if (!b.turn && b.board[0] == "_b_b_b_b" && b.board[1] == "b_b_b_b_" && b.board[2] == "_b_b_b_b"
		&& b.board[5] == "w_w_w_w_" && b.board[6] == "_w_w_w_w" && b.board[7] == "w_w_w_w_")
	{
		Move bopen;
		bopen.r0 = 2; bopen.c0 = 1; bopen.rf = 3; bopen.cf = 0;
		return bopen;
	}

	Move best;
	vector<Move> mvlist = generateMoves(b);
	best = mvlist[0]; //random move is best by default
                              
	int highScore = staticEval(b);
    
	MoveScore neg;
	neg.m = best;
	neg.score = -99999999;
	MoveScore pos;
	pos.m = best;
	pos.score = 99999999;
			
        MoveScore ms = alphabetaMax(b, neg, pos, depth);
        highScore = ms.score;
        best = ms.m;
	cerr << "High: " << highScore << "\n";
        return best;
}

int main()
{
	char turn;
	cin.get(turn);
	int sz;
	cin >> sz;
	cin.ignore(1000, '\n');
	Board m_board;
	string line;
	
	for (int i = 0; i < sz; i++)
	{
		getline(cin, line);
		m_board.board.push_back(line);
	}
	m_board.turn = turn == 'w';	
	vector<Move> legalMoves = generateMoves(m_board);
	
	ostringstream pikachu;
	int nmoves = 1;
	Move f = legalMoves[0];
	f = evaluate(m_board, 7);
	pikachu << f.r0 << " " << f.c0 << "\n" << f.rf << " " << f.cf << "\n";
	int last = f.rf*10 + f.cf;
		
	bool capt = abs(f.rf - f.r0) == 2;
	while (capt)
	{
		capt = false;
		m_board = makeMove(m_board, f);
		legalMoves = generateMoves(m_board);
		for (Move m : legalMoves)
		{
			if (abs(m.rf - m.r0) == 2 && (m.r0*10 + m.c0) == last)
			{
				f = m;
				pikachu << f.rf << " " << f.cf << "\n";
				last = f.rf*10 + f.cf;
				nmoves++;
				capt = true;
				break;
			}
		}
	}
		
	cout << nmoves << "\n" << pikachu.str();

	return 0;
}