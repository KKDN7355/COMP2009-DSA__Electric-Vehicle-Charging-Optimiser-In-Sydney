#ifndef LOCATION_H_
#define LOCATION_H_

class Location {
public:
	int		index;
	string	name;
	bool	charger_installed;
	double	charging_price;

	void print() {
		cout << setw (6) << index << setw (20) << name << setw (15);
		if (charger_installed) {
			cout << "T";
		}
		else {
			cout << "F";
		}

		if (!charger_installed) {
			cout << setw(23) << "N/A" << endl;
		}
		else {
			cout << setw(17) << "$" << fixed << setprecision(2) << charging_price << "/kWh" << endl;
		}
	}

	bool operator<(const Location& l)  const {
		if (charger_installed != l.charger_installed) {
			return charger_installed < l.charger_installed;
		}
		else if (charging_price != l.charging_price) {
			return charging_price > l.charging_price;
		}
		else {
			return index > l.index;
		}
	}

	bool operator==(const Location& l) const {
		return index == l.index && name == l.name && charger_installed == l.charger_installed && charging_price == l.charging_price;
	}

	bool operator!=(const Location& l) const {
		return !(*this == l);
	}
};

#endif /* LOCATION_H_ */