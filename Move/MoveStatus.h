#ifndef MOVE_STATUS_H
#define MOVE_STATUS_H 

enum MoveStatus {
	SUCCESS,
	LEAVES_PLAYER_IN_CHECK,
	ILLEGAL
};

std::ostream& operator <<(std::ostream& out, MoveStatus status){
	switch(status){
		case SUCCESS: return out << "SUCCESS";
		case LEAVES_PLAYER_IN_CHECK: return out << "LEAVES_PLAYER_IN_CHECK";
		case ILLEGAL: return out << "ILLEGAL";
		default: throw std::invalid_argument("Unknown MoveStatus!");
	}
}

#endif