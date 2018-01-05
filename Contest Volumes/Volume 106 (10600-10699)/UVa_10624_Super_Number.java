
// UVa 10624 - Super Number

import java.util.Scanner;
import java.math.BigInteger;

class Main {
/*
	static final int nMax = 28, mMax = 29;
	static final BigInteger MINUS_ONE = BigInteger.ZERO.subtract(BigInteger.ONE);
	static BigInteger superNumbers[][] = new BigInteger[nMax + 1][mMax + 1];

	static boolean superNumber(int n, int ni, BigInteger s) {
		ni++;
		BigInteger t = s.multiply(BigInteger.TEN), bni = BigInteger.valueOf(ni);
		int i = 0;
		while (true) {
			if (t.remainder(bni).compareTo(BigInteger.ZERO) == 0) {
				if (superNumbers[n][ni].compareTo(MINUS_ONE) == 0) {
					superNumbers[n][ni] = t;
				}
				if (ni == mMax || superNumber(n, ni, t))
					return true;
			}
			if (++i == 10)
				break;
			t = t.add(BigInteger.ONE);
		}
		return false;
	}
*/

static final String superNumbers[][] = {
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1"},
{"-1", "-1", "10", "102", "1020", "10200", "102000", "1020005", "10200056", "102000564", "1020005640", "10200056405", "102006162060", "1020061620604", "10200616206046", "102006162060465", "1020061620604656", "10200616206046568", "108054801036000018", "1080548010360000180", "10805480103600001800", "123606009012225672009", "1236060090122256720090", "12360600901222567200901", "144408645048225636603816", "3608528850368400786036725", "-1", "-1", "-1", "-1"},
{"-1", "-1", "-1", "102", "1020", "10200", "102000", "1020005", "10200056", "102000564", "1020005640", "10200056405", "102006162060", "1020061620604", "10200616206046", "102006162060465", "1020061620604656", "10200616206046568", "108054801036000018", "1080548010360000180", "10805480103600001800", "123606009012225672009", "1236060090122256720090", "12360600901222567200901", "144408645048225636603816", "3608528850368400786036725", "-1", "-1", "-1", "-1"},
{"-1", "-1", "-1", "-1", "1020", "10200", "102000", "1020005", "10200056", "102000564", "1020005640", "10200056405", "102006162060", "1020061620604", "10200616206046", "102006162060465", "1020061620604656", "10200616206046568", "108054801036000018", "1080548010360000180", "10805480103600001800", "123606009012225672009", "1236060090122256720090", "12360600901222567200901", "144408645048225636603816", "3608528850368400786036725", "75320424003636007240884008", "753204240036360072408840084", "7532042400363600724088400840", "-1"},
{"-1", "-1", "-1", "-1", "-1", "10000", "100002", "1000020", "10000200", "100002006", "1000020060", "10000200606", "100002006060", "1000027260128", "10000272601284", "100002726012840", "1000027260128400", "10000832402470569", "101208807048720006", "1016582400964208520", "10165824009642085200", "104052249072240066402", "1040522490722400664022", "10405224907224006640223", "144408645048225636603816", "1828022400607200846092400", "18280224006072008460924002", "753204240036360072408840084", "7532042400363600724088400840", "-1"},
{"-1", "-1", "-1", "-1", "-1", "-1", "100002", "1000020", "10000200", "100002006", "1000020060", "10000200606", "100002006060", "1000027260128", "10000272601284", "100002726012840", "1000027260128400", "10000832402470569", "100956888012540816", "1016582400964208520", "10165824009642085200", "104052249072240066402", "1040522490722400664022", "10405224907224006640223", "119952000084840030408408", "1301587290367056900064800", "13015872903670569000648008", "528552567072465642000840006", "7532042400363600724088400840", "-1"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "1000020", "10000200", "100002006", "1000020060", "10000200606", "100002006060", "1000027260128", "10000272601284", "100002726012840", "1000027260128400", "10000832402470569", "100116162084960054", "1001406420365408286", "10014064203654082860", "101082888060705684000", "1029126420361200420006", "10326688207290084640567", "103266882072900846405672", "1032668820729008464056725", "10326688207290084640567258", "392088960012120066801672588", "3920889600121200668016725880", "39208896001212006680167258804"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "10000064", "100000647", "1000006470", "10000064701", "100000647012", "1000006470125", "10000064701256", "100001367072180", "1000013670721808", "10000136707218087", "100003446072465678", "1000034460724656782", "10000344607246567820", "100003446072465678204", "1000034460724656782040", "10022184007290082800925", "100706967024300864801288", "1012788810007808586060725", "10326688207290084640567258", "140865282036780876603600003", "1408652820367808766036000036", "18555536703606084000060008482"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "100000008", "1000000080", "10000000802", "100000008024", "1000000080248", "10000000802484", "100000008024840", "1000000080248400", "10000072808446565", "100001763072960030", "1000017630729600301", "10000344607246567820", "100003446072465678204", "1000034460724656782040", "10003824006022562480160", "100038240060225624801600", "1000382400602256248016000", "10003824006022562480160006", "100038240060225624801600066", "1015500060367808224022400608", "10211576408418088880443254681"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "1000000080", "10000000802", "100000008024", "1000000080248", "10000000802484", "100000008024840", "1000000080248400", "10000001704812002", "100000179072360072", "1000001880969008586", "10000018809690085860", "100000188096900858606", "1000001880969008586064", "10001501103622563080700", "100015011036225630807000", "1000150110362256308070000", "10003824006022562480160006", "100038240060225624801600066", "1001385810724656966004325888", "10101279606082569080443254680"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "10000000109", "100000002084", "1000000060449", "10000000604496", "100000006044960", "1000000060449600", "10000001209254080", "100000012092540804", "1000000130883600069", "10000011901236001220", "100000119012360012201", "1000001190123600122018", "10000084204894563040805", "100004993004840012201288", "1000080030482400064054325", "10000800304824000640543250", "100019420052585642609000003", "1001159170089456786034325496", "10015192000842085860660000924"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "100000000104", "1000000005485", "10000000054856", "100000000764300", "1000000007643008", "10000000087224007", "100000004832000090", "1000000073644656126", "10000000736446561260", "100000007364465612600", "1000000122004800908046", "10000001220048009080461", "100000146732225624801456", "1000004058963008284086000", "10000155957610563000967256", "100001559576105630009672561", "1000023746761200244028400000", "10000351372830084060967250126"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "1000000000207", "10000000002076", "100000000020765", "1000000000805408", "10000000008054089", "100000000200105630", "1000000002001056306", "10000000020010563060", "100000002384105660606", "1000000023841056606060", "10000000881654084060982", "100000019772945648006240", "1000000197729456480062400", "10000007881248007860384004", "100000093788420804006672546", "1000000937884208040066725460", "10000028419290081060024006085"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "10000000000256", "100000000006485", "1000000000077456", "10000000001166080", "100000000011660804", "1000000000480656242", "10000000004806562420", "100000000120860810600", "1000000003548000244020", "10000000035480002440203", "100000000579785678204888", "1000000050595056546002400", "10000001600946082840848006", "100000038191340816606000042", "1000000381913408166060000420", "10000003819134081660600004206"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "100000000000185", "1000000000001856", "10000000000018563", "100000000000740852", "1000000000015808227", "10000000000438565400", "100000000009140894201", "1000000000091408942010", "10000000001964009660049", "100000000038825612600600", "1000000000388256126006000", "10000000106166087000943258", "100000001748780810600072507", "1000000029931056724086725040", "10000000299310567240867250403"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "1000000000000208", "10000000000006561", "100000000000065618", "1000000000000656183", "10000000000027522820", "100000000000635282009", "1000000000006352820090", "10000000000939521680145", "100000000009395216801456", "1000000000116752586006725", "10000000001167525860067258", "100000000061160048003000087", "1000000004165856722072400216", "10000000177423525880167258806"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "10000000000000169", "100000000000006452", "1000000000000064523", "10000000000003042840", "100000000000033650804", "1000000000001744104022", "10000000000021606220147", "100000000000441656801480", "1000000000004416568014800", "10000000000044165680148008", "100000000000441656801480087", "1000000000484656388074325076", "10000000012965287440500008129"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "100000000000000332", "1000000000000003324", "10000000000000033240", "100000000000001016405", "1000000000000010164056", "10000000000000101640564", "100000000000001016405648", "1000000000004416568014800", "10000000000044165680148008", "100000000000441656801480087", "1000000000011882960090000000", "10000000000552924880760008767"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "1000000000000000265", "10000000000000006260", "100000000000000062606", "1000000000000000626066", "10000000000000006260668", "100000000000001016405648", "1000000000000019702046000", "10000000000001107880743258", "100000000000023444006480081", "1000000000000273504056000848", "10000000000010730620467258241"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "10000000000000000180", "100000000000000039800", "1000000000000000474024", "10000000000000005880501", "100000000000000123401432", "1000000000000001234014325", "10000000000000036280107256", "100000000000001164602000024", "1000000000000013964006000428", "10000000000000635540300008128"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "100000000000000000005", "1000000000000000000056", "10000000000000000120243", "100000000000000001202432", "1000000000000000012024325", "10000000000000000120243256", "100000000000000001202432561", "1000000000000002242010000420", "10000000000000024060207252565"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "1000000000000000000056", "10000000000000000008923", "100000000000000000131096", "1000000000000000010550000", "10000000000000000105500008", "100000000000000001055000087", "1000000000000000047092400272", "10000000000000000485667250123"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "10000000000000000000344", "100000000000000000003440", "1000000000000000000034400", "10000000000000000001448008", "100000000000000000014480081", "1000000000000000006062725880", "10000000000000000135423252801"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "100000000000000000000224", "1000000000000000000006800", "10000000000000000000068006", "100000000000000000004592546", "1000000000000000000045925468", "10000000000000000007244006366"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "1000000000000000000000325", "10000000000000000000015252", "100000000000000000000392507", "1000000000000000000003925076", "10000000000000000001503258209"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "10000000000000000000000250", "100000000000000000000017585", "1000000000000000000000225268", "10000000000000000000006750880"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "100000000000000000000000683", "1000000000000000000000022492", "10000000000000000000000224923"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "1000000000000000000000000624", "10000000000000000000000141200"},
{"-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "-1", "10000000000000000000000000086"}
};

	public static void main(String[] args) {
/*
		for (int n = 1; n <= nMax; n++) {
			for (int m = n + 1; m <= mMax; m++)
				superNumbers[n][m] = MINUS_ONE;
			BigInteger bn = BigInteger.valueOf(n), s = BigInteger.TEN.pow(n - 1), t = s.multiply(BigInteger.TEN);
			for (s = s.add(bn).subtract(BigInteger.ONE).divide(bn).multiply(bn); s.compareTo(t) < 0; s = s.add(bn))
				if (superNumber(n, n, s))
					break;
		}

		System.out.println("static final String superNumbers[][] = {");
		for (int n = 0; n <= nMax; n++)
			for (int m = 0; m <= mMax; m++) {
				if (m == 0)
					System.out.print("{");
				System.out.print("\"" + ((superNumbers[n][m] != null) ? superNumbers[n][m] : MINUS_ONE) + "\"");
				if (m < mMax)
					System.out.print(", ");
				else {
					if (n < nMax)
						System.out.println("},");
					else
						System.out.println("}");
				}
			}
		System.out.println("};");
*/

		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		for (int ti = 1; ti <= t; ti++) {
			int n = sc.nextInt(), m = sc.nextInt();
			System.out.println("Case " + ti + ": " + superNumbers[n][m]);
		}
	}
}

/*
Sample Input

2
1 10
3 29

Sample Output

Case 1: 1020005640
Case 2: -1
*/

