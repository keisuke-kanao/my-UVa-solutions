
// UVa 11947 - Cancer or Scorpio

import java.util.Scanner;
import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.util.Date;
import java.util.Calendar;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.ListIterator;

class Main {
	public static void main(String[] args) {
		SimpleDateFormat parseFormat = new SimpleDateFormat("MMddyyyy"), printFormat = new SimpleDateFormat("MM/dd/yyyy");
		Calendar cal = Calendar.getInstance();
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		for (int i = 1; i <= N; i++) {
			try {
				Date date = parseFormat.parse(sc.next());
				cal.setTime(date);
				cal.add(Calendar.WEEK_OF_YEAR, 40);
				String name = ZodiacSign.getZodiacSign(isLeapYear(cal.get(Calendar.YEAR)),
					cal.get(Calendar.DAY_OF_YEAR));
				System.out.println(i + " " + printFormat.format(cal.getTime()) + " " + name);
			}
			catch (ParseException e) {
			}
		}
	}

	static boolean isLeapYear(int year) {
    	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	}
}

class ZodiacSign {
	final String name;
	final int begin, end;

	ZodiacSign(String name, int begin, int end) {
		this.name = name; this.begin = begin; this.end = end;
	}

	static final ArrayList<ZodiacSign> zodiacSigns = new ArrayList<ZodiacSign>(Arrays.asList(
		new ZodiacSign("capricorn",          1,        20),
		new ZodiacSign("aquarius",          21,   31 + 19),
		new ZodiacSign("pisces",       31 + 20,   59 + 20),
		new ZodiacSign("aries",        59 + 21,   90 + 20),
		new ZodiacSign("taurus",       90 + 21,  120 + 21),
		new ZodiacSign("gemini",      120 + 22,  151 + 21),
		new ZodiacSign("cancer",      151 + 22,  181 + 22),
		new ZodiacSign("leo",         181 + 23,  212 + 21),
		new ZodiacSign("virgo",       212 + 22,  243 + 23),
		new ZodiacSign("libra",       243 + 24,  273 + 23),
		new ZodiacSign("scorpio",     273 + 24,  304 + 22),
		new ZodiacSign("sagittarius", 304 + 23,  334 + 22),
		new ZodiacSign("capricorn",   334 + 23,  334 + 31)
	));

	static final ArrayList<ZodiacSign> leapYearZodiacSigns = new ArrayList<ZodiacSign>(Arrays.asList(
		new ZodiacSign("capricorn",          1,        20),
		new ZodiacSign("aquarius",          21,   31 + 19),
		new ZodiacSign("pisces",       31 + 20,   60 + 20),
		new ZodiacSign("aries",        60 + 21,   91 + 20),
		new ZodiacSign("taurus",       91 + 21,  121 + 21),
		new ZodiacSign("gemini",      121 + 22,  152 + 21),
		new ZodiacSign("cancer",      152 + 22,  182 + 22),
		new ZodiacSign("leo",         182 + 23,  213 + 21),
		new ZodiacSign("virgo",       213 + 22,  244 + 23),
		new ZodiacSign("libra",       244 + 24,  274 + 23),
		new ZodiacSign("scorpio",     274 + 24,  305 + 22),
		new ZodiacSign("sagittarius", 305 + 23,  335 + 22),
		new ZodiacSign("capricorn",   335 + 23,  335 + 31)
	));

	static String getZodiacSign(boolean leapYear, int dayOfYear) {
		final ArrayList<ZodiacSign> list = (leapYear) ? leapYearZodiacSigns : zodiacSigns;
		String name = "";
		for (ListIterator<ZodiacSign> i = list.listIterator(); i.hasNext(); ) {
			ZodiacSign zs = i.next();
			if (dayOfYear >= zs.begin && dayOfYear <= zs.end) {
				name = zs.name; break;
			}
		}
		return name;
     }
}

