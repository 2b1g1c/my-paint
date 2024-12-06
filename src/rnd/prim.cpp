#include <string>
#include "prim.hpp"

#include "rnd/prim.hpp"
#include "rnd/ssbo.hpp"
#include "rnd/shader.hpp"

mr::Prim::~Prim() noexcept
{
  glDeleteVertexArrays(1, &_va);
  glDeleteBuffers(1, &_vbuf);
  glDeleteBuffers(1, &_ibuf);
}

void mr::Prim::draw(const mr::SSBO<Transform> &ssbo) const noexcept {
  ssbo.apply();
  glBindVertexArray(_va);

  if (_ibuf == 0) {
    glDrawArraysInstanced(
      (uint32_t)_ttype, 0, _num_of_elements, ssbo.size());
  }
  else {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibuf);
    glDrawElementsInstanced((uint32_t)_ttype,
                            _num_of_elements,
                            GL_UNSIGNED_INT,
                            NULL,
                            ssbo.size());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  /* Turning vertex array off */
  glBindVertexArray(0);
}

mr::Prim mr::create_circle() noexcept {
  using vec2 = float[2];
  // (2pi / 0.01) vertices
  vec2 vertices[] = {
    {                   1.0,                 -0.01},
    {    0.9999500004166653,  0.009999833334166664},
    {    0.9998000066665778,   0.01999866669333308},
    {    0.9995500337489875,   0.02999550020249566},
    {    0.9992001066609779,   0.03998933418663416},
    {    0.9987502603949663,   0.04997916927067833},
    {    0.9982005399352042,    0.0599640064794446},
    {    0.9975510002532796,   0.06994284733753277},
    {    0.9968017063026194,    0.0799146939691727},
    {    0.9959527330119943,   0.08987854919801104},
    {    0.9950041652780258,   0.09983341664682814},
    {    0.9939560979566968,    0.1097783008371748},
    {    0.9928086358538663,   0.11971220728891935},
    {    0.9915618937147881,   0.12963414261969483},
    {    0.9902159962126372,   0.13954311464423647},
    {    0.9887710779360422,   0.14943813247359922},
    {    0.9872272833756269,   0.15931820661424598},
    {    0.9855847669095608,   0.16918234906699603},
    {    0.9838436927881214,    0.1790295734258242},
    {    0.9820042351172703,    0.1888588949765006},
    {    0.9800665778412416,   0.19866933079506124},
    {    0.9780309147241483,    0.2084598998460996},
    {    0.9758974493306055,   0.21822962308086938},
    {    0.9736663950053748,   0.22797752353518846},
    {    0.9713379748520296,   0.23770262642713466},
    {    0.9689124217106447,     0.247403959254523},
    {    0.9663899781345132,    0.2570805518921552},
    {    0.9637708963658905,    0.2667314366888312},
    {    0.9610554383107709,    0.2763556485641138},
    {    0.9582438755126972,   0.28595222510483564},
    {     0.955336489125606,   0.29552020666133966},
    {    0.9523335698857134,    0.3050586364434436},
    {    0.9492354180824408,    0.3145665606161179},
    {    0.9460423435283869,    0.3240430283948685},
    {    0.9427546655283462,    0.3334870921408145},
    {    0.9393727128473789,    0.3428978074554515},
    {    0.9358968236779348,    0.3522742332750901},
    {    0.9323273456060344,   0.36161543196496215},
    {    0.9286646355765101,   0.37092046941298285},
    {     0.924909059857313,    0.3801884151231616},
    {     0.921060994002885,    0.3894183423086507},
    {     0.917120822816605,   0.39860932798442306},
    {    0.9130889403123081,   0.40776045305957037},
    {    0.9089657496748851,     0.416870802429211},
    {    0.9047516632199634,    0.4259394650659998},
    {    0.9004471023526768,    0.4349655341112304},
    {    0.8960524975255252,      0.44394810696552},
    {    0.8915682881953289,    0.4528862853790685},
    {     0.886994922779284,    0.4617791755414831},
    {    0.8823328586101213,   0.47062588817115825},
    {    0.8775825618903726,   0.47942553860420317},
    {    0.8727445076457512,    0.4881772468829077},
    {    0.8678191796776498,    0.4968801378437369},
    {    0.8628070705147609,    0.5055333412048472},
    {     0.857708681363824,    0.5141359916531133},
    {    0.8525245220595056,    0.5226872289306594},
    {     0.847255111013416,    0.5311861979208836},
    {    0.8419009751622686,    0.5396320487339695},
    {    0.8364626499151868,    0.5480239367918738},
    {    0.8309406791001633,     0.556361022912784},
    {    0.8253356149096781,    0.5646424733950356},
    {    0.8196480178454794,    0.5728674601004815},
    {    0.8138784566625338,    0.5810351605373053},
    {    0.8080275083121516,    0.5891447579422698},
    {    0.8020957578842924,    0.5971954413623923},
    {    0.7960837985490556,    0.6051864057360399},
    {    0.7899922314973649,    0.6131168519734341},
    {     0.783821665880849,    0.6209859870365599},
    {    0.7775727187509277,    0.6287930240184688},
    {    0.7712460149971063,    0.6365371822219682},
    {    0.7648421872844882,    0.6442176872376913},
    {    0.7583618759905079,     0.651833771021537},
    {    0.7518057291408947,    0.6593846719714734},
    {    0.7451744023448701,    0.6668696350036982},
    {    0.7384685587295876,    0.6742879116281454},
    {    0.7316888688738206,    0.6816387600233345},
    {    0.7248360107409049,    0.6889214451105516},
    {    0.7179106696109431,     0.696135238627357},
    {    0.7109135380122771,    0.7032794192004105},
    {    0.7038453156522357,    0.7103532724176082},
    {     0.696706709347165,    0.7173560908995231},
    {    0.6894984329517466,    0.7242871743701429},
    {    0.6822212072876132,    0.7311458297268962},
    {    0.6748757600712667,    0.7379313711099631},
    {    0.6674628258413078,    0.7446431199708596},
    {    0.6599831458849817,     0.751280405140293},
    {    0.6524374681640515,    0.7578425628952773},
    {    0.6448265472400008,    0.7643289370255054},
    {    0.6371511441985798,    0.7707388788989696},
    {    0.6294120265736964,    0.7770717475268242},
    {    0.6216099682706641,    0.7833269096274837},
    {    0.6137457494888111,    0.7895037396899508},
    {    0.6058201566434623,    0.7956016200363664},
    {    0.5978339822872978,    0.8016199408837775},
    {    0.5897880250310977,    0.8075581004051147},
    {     0.581683089463883,    0.8134155047893741},
    {    0.5735199860724561,    0.8191915683009986},
    {    0.5652995311603538,    0.8248857133384504},
    {    0.5570225467662168,    0.8304973704919708},
    {     0.548689860581587,    0.8360259786005209},
    {    0.5403023058681392,    0.8414709848078968},
    {    0.5318607213743549,    0.8468318446180155},
    {     0.523365951251649,    0.8521080219493633},
    {    0.5148188449699548,    0.8572989891886037},
    {    0.5062202572327777,    0.8624042272433388},
    {   0.49757104789172635,    0.8674232255940173},
    {   0.48887208186052694,    0.8723554823449866},
    {   0.48012422902853347,     0.877200504274682},
    {   0.47132836417373936,    0.8819578068849478},
    {   0.46248536687530023,    0.8866269144494876},
    {    0.4535961214255767,    0.8912073600614356},
    {    0.4446615167417062,     0.895698685680048},
    {    0.4356824462767115,    0.9001004421765053},
    {    0.4266598079301566,    0.9044121893788263},
    {    0.4175945039583574,    0.9086334961158836},
    {   0.40848744088415656,    0.9127639402605214},
    {   0.39933952940627243,    0.9168031087717673},
    {   0.39015168430822944,     0.920750597736136},
    {     0.380924824366881,    0.9246060124080206},
    {   0.37165987226053215,     0.928368967249167},
    {    0.3623577544766728,    0.9320390859672266},
    {   0.35301940121932956,    0.9356160015533862},
    {    0.3436457463160462,    0.9390993563190678},
    {    0.3342377271245018,    0.9424888019316978},
    {    0.3247962844387754,    0.9457839994495393},
    {   0.31532236239526784,    0.9489846193555865},
    {   0.30581690837828845,    0.9520903415905161},
    {   0.29628087292531785,    0.9551008555846925},
    {    0.2867152096319546,    0.9580158602892253},
    {   0.27712087505655675,    0.9608350642060729},
    {    0.2674988286245865,    0.9635581854171932},
    {   0.25785003253266875,    0.9661849516127343},
    {   0.24817545165237204,    0.9687151001182654},
    {   0.23847605343372227,    0.9711483779210448},
    {   0.22875280780845852,    0.9734845416953196},
    {   0.21900668709304064,    0.9757233578266593},
    {    0.2092386658914184,    0.9778646024353164},
    {     0.199449720997572,    0.9799080613986144},
    {   0.18964083129783338,    0.9818535303723599},
    {   0.17981297767299848,    0.9837008148112767},
    {   0.16996714290023993,    0.9854497299884604},
    {   0.16010431155483018,    0.9871001010138505},
    {   0.15022546991168476,      0.98865176285172},
    {   0.14033160584673562,     0.990104560337178},
    {   0.13042370873814443,    0.9914583481916867},
    {   0.12050276936736551,    0.9927129910375886},
    {   0.11056977982006848,     0.993868363411645},
    {   0.10062573338693062,     0.994924349777581},
    {   0.09067162446430857,    0.9958808445376401},
    {   0.08070844845479952,    0.9967377520431435},
    {    0.0707372016677018,    0.9974949866040546},
    {   0.06075888121938479,    0.9981524724975482},
    {   0.05077448493357807,    0.9987101439755831},
    {  0.040785011241589925,     0.999167945271476},
    {   0.03079145908246501,    0.9995258306054791},
    {   0.02079482780309132,     0.999783764189357},
    {  0.010796117058266282,    0.9999417202299663},
    { 0.0007963267107321531,    0.9999996829318346},
    { -0.009203543268809447,    0.9999576464987401},
    {  -0.01920249290169376,    0.9998156151342908},
    { -0.029199522301289926,    0.9995736030415051},
    {  -0.03919363177298882,    0.9992316344213905},
    {  -0.04918382191417166,     0.998789743470524},
    {  -0.05916909371414947,    0.9982479743776324},
    {  -0.06914844865406328,    0.9976063813191736},
    {  -0.07912088880673519,    0.9968650284539188},
    {  -0.08908541693646028,    0.9960239899165366},
    {  -0.09904103659872934,    0.9950833498101801},
    {  -0.10898675223987243,    0.9940432021980758},
    {  -0.11892156929661354,    0.9929036510941184},
    {  -0.12884449429552597,    0.9916648104524685},
    {  -0.13875453495237888,    0.9903268041561579},
    {  -0.14865070027136496,    0.9888897660047012},
    {  -0.15853200064419906,    0.9873538397007162},
    {  -0.16839744794907832,    0.9857191788355533},
    {   -0.1782460556494934,    0.9839859468739367},
    {  -0.18807683889288143,    0.9821543171376182},
    {  -0.19788881460911031,    0.9802244727880453},
    {   -0.2076810016087851,    0.9781966068080444},
    {  -0.21745242068136594,    0.9760709219825239},
    {  -0.22720209469308839,    0.9738476308781949},
    {  -0.23692904868467599,     0.971526955822315},
    {   -0.2466323099688353,    0.9691091288804561},
    {    -0.256310908227524,    0.9665943918332972},
    {  -0.26596387560898166,    0.9639829961524478},
    {   -0.2755902468245142,    0.9612752029752996},
    {  -0.28518905924502214,    0.9584712830789138},
    {  -0.29475935299726225,    0.9555715168529435},
    {   -0.3043001710598347,    0.9525761942715949},
    {  -0.31381055935888374,      0.94948561486463},
    {   -0.3232895668635048,     0.946300087687414},
    {  -0.33273624568084664,      0.94301993129001},
    {   -0.3421496511508996,    0.9396454736853244},
    {   -0.3515288419409613,    0.9361770523163055},
    {   -0.3608728801397686,    0.9326150140221999},
    {   -0.3701808313512883,    0.9289597150038688},
    {   -0.3794517647881559,    0.9252115207881677},
    {  -0.38868475336475344,    0.9213708061913948},
    {   -0.3978788737899174,    0.9174379552818093},
    {  -0.40703320665926696,    0.9134133613412245},
    {   -0.4161468365471436,    0.9092974268256812},
    {   -0.4252188520981534,    0.9050905633252004},
    {  -0.43424834611830126,    0.9007931915226269},
    {   -0.4432344156657097,    0.8964057411515596},
    {   -0.4521761621409124,    0.8919286509533794},
    {  -0.46107269137671314,    0.8873623686333753},
    {   -0.4699231137276022,    0.8827073508159741},
    {   -0.4787265441587198,    0.8779640629990781},
    {    -0.487482102334359,    0.8731329795075167},
    {  -0.49618891270599846,    0.8682145834456129},
    {   -0.5048461045998568,    0.8632093666488742},
    {   -0.5134528123039588,    0.8581178296348094},
    {   -0.5220081751547062,    0.8529404815528769},
    {   -0.5305113376229437,    0.8476778401335705},
    {   -0.5389614493995101,    0.8423304316366466},
    {   -0.5473576654802695,    0.8368987907984987},
    {   -0.5556991462506109,    0.8313834607786843},
    {   -0.5639850575694082,    0.8257849931056094},
    {   -0.5722145708524347,    0.8201039476213756},
    {   -0.5803868631552197,    0.8143408924257975},
    {   -0.5885011172553434,    0.8084964038195919},
    {   -0.5965565217341574,    0.8025710662467491},
    {   -0.6045522710579269,    0.7965654722360886},
    {   -0.6124875656583824,     0.790480222342007},
    {   -0.6203616120126767,    0.7843159250844224},
    {    -0.628173622722736,    0.7780731968879238},
    {   -0.6359228165939993,    0.7717526620201285},
    {   -0.6436084187135371,    0.7653549525292563},
    {   -0.6512296605275422,    0.7588807081809249},
    {   -0.6587857799181841,    0.7523305763941739},
    {   -0.6662760212798204,    0.7457052121767236},
    {    -0.673699635594557,    0.7390052780594745},
    {   -0.6810558805071486,    0.7322314440302551},
    {   -0.6883440203992341,    0.7253843874668235},
    {   -0.6955633264628979,    0.7184647930691302},
    {   -0.7027130767735495,    0.7114733527908488},
    {   -0.7097925563621161,    0.7044107657701806},
    {   -0.7168010572865383,    0.6972777382599425},
    {    -0.723737878702564,    0.6900749835569413},
    {   -0.7306023269338324,    0.6828032219306449},
    {   -0.7373937155412407,    0.6754631805511563},
    {   -0.7441113653915875,    0.6680555934164966},
    {   -0.7507546047254859,    0.6605812012792064},
    {   -0.7573227692245386,    0.6530407515722708},
    {   -0.7638152020777689,    0.6454349983343768},
    {   -0.7702312540473021,    0.6377647021345101},
    {   -0.7765702835332877,    0.6300306299958988},
    {   -0.7828316566380599,    0.6222335553193116},
    {   -0.7890147472295257,    0.6143742578057187},
    {   -0.7951189370037787,    0.6064535233783221},
    {   -0.8011436155469281,     0.598472144103964},
    {   -0.8070881803961404,    0.5904309181139206},
    {   -0.8129520370998843,    0.5823306495240899},
    {    -0.818734599277376,    0.5741721483545806},
    {   -0.8244352886772165,    0.5659562304487112},
    {   -0.8300535352352164,    0.5576837173914255},
    {   -0.8355887771314018,    0.5493554364271356},
    {   -0.8410404608461957,    0.5409722203769975},
    {   -0.8464080412157696,    0.5325349075556305},
    {   -0.8516909814865598,    0.5240443416872855},
    {   -0.8568887533689413,     0.515501371821474},
    {   -0.8620008370900576,    0.5069068522480634},
    {   -0.8670267214457965,   0.49826164241184895},
    {   -0.8719659038519106,   0.48956660682660996},
    {   -0.8768178903942755,   0.48082261498865914},
    {     -0.88158219587828,   0.47203054128989363},
    {    -0.886258343877346,   0.46319126493035656},
    {   -0.8908458667805706,   0.45430566983031795},
    {   -0.8953443058394861,    0.4453746445418831},
    {   -0.8997532112139355,    0.4363990821601383},
    {   -0.9040721420170553,    0.4273798802338422},
    {   -0.9083006663593644,   0.41831794067567146},
    {   -0.9124383613919522,    0.4092141696720303},
    {   -0.9164848133487636,   0.40006947759243255},
    {    -0.920439617587975,    0.3908847788984657},
    {   -0.9243023786324579,   0.38166099205234527},
    {   -0.9280727102093271,    0.3723990394250693},
    {   -0.9317502352885667,   0.36309984720418237},
    {   -0.9353345861207334,   0.35376434530115725},
    {   -0.9388254042737308,    0.3443934672584046},
    {   -0.9422223406686528,    0.3349881501559197},
    {   -0.9455250556146907,    0.3255493345175751},
    {    -0.948733218843102,   0.31607796421706896},
    {   -0.9518465095402373,    0.3065749863835386},
    {   -0.9548646163796215,    0.2970413513068481},
    {   -0.9577872375530855,   0.28747801234256054},
    {   -0.9606140808009476,     0.277885925816603},
    {   -0.9633448634412386,    0.2682660509296346},
    {   -0.9659793123979703,   0.25861934966112754},
    {   -0.9685171642284423,   0.24894678667316977},
    {   -0.9709581651495862,   0.23924932921399966},
    {   -0.9733020710633444,   0.22952794702128193},
    {   -0.9755486475810786,    0.2197836122251347},
    {   -0.9776976700470092,    0.2100172992509174},
    {   -0.9797489235606806,    0.2002299847217888},
    {   -0.9817022029984505,    0.1904226473610458},
    {    -0.983557313034003,    0.1805962678942517},
    {   -0.9853140681578805,   0.17075182895116459},
    {   -0.9869722926960345,   0.16089031496747505},
    {    -0.988531820827393,    0.1510127120863636},
    {   -0.9899924966004426,     0.141120008059887},
    {   -0.9913541739488232,   0.13121319215020405},
    {   -0.9926167167059347,   0.12129325503065003},
    {   -0.9937799986185533,   0.11136118868667032},
    {   -0.9948439033594574,   0.10141798631662263},
    {   -0.9958083245390593,   0.09146464223245798},
    {   -0.9966731657160448,   0.08150215176029037},
    {    -0.997438340407017,   0.07153151114086496},
    {   -0.9981037720951443,  0.061553717429934866},
    {   -0.9986693942378124,   0.05156976839855636},
    {   -0.9991351502732786,  0.041580662433312675},
    {   -0.9995009936263272,  0.031587398436476094},
    {   -0.9997668877129279,    0.0215909757261186},
    {   -0.9999328059438936,  0.011592393936180922},
    {   -0.9999987317275395, 0.0015926529165099209},
    {   -0.9999646584713422, -0.008407247367125526},
    {   -0.9998305895825987, -0.018406306933030275},
    {   -0.9995965384680865,  -0.02840352588358026},
    {   -0.9992625285327218,  -0.03839790450521142},
    {   -0.9988285931772198,   -0.0483884433683902},
    {   -0.9982947757947545,   -0.0583741434275557},
    {   -0.9976611297666192,  -0.06835400612102341},
    {   -0.9969277184568889,  -0.07832703347084051},
    {   -0.9960946152060831,  -0.08829222818258282},
    {   -0.9951619033238328,  -0.09824859374508349},
    {   -0.9941296760805489,  -0.10819513453008321},
    {   -0.9929980366980957,  -0.11813085589179223},
    {   -0.9917670983394682,  -0.12805476426635412},
    {   -0.9904369840974767,  -0.13796586727120133},
    {   -0.9890078269824367,   -0.1478631738042926},
    {   -0.9874797699088691,  -0.15774569414322234},
    {   -0.9858529656812075,  -0.16761244004419204},
    {   -0.9841275769785193,   -0.1774624248408339},
    {   -0.9823037763382367,  -0.18729466354287658},
    {   -0.9803817461389042,   -0.1971081729346433},
    {   -0.9783616785819398,  -0.20690197167337282},
    {   -0.9762437756724158,  -0.21667508038735275},
    {   -0.9740282491988584,   -0.2264265217738559},
    {   -0.9717153207120687,   -0.2361553206968698},
    {   -0.9693052215029678,  -0.24586050428460948},
    {   -0.9667981925794683,  -0.25554110202680375},
    {   -0.9641944846423733,  -0.26519614587174556},
    {   -0.9614943580603068,  -0.27482467032309627},
    {   -0.9586980828436769,  -0.28442571253643445},
    {    -0.955805938617675,   -0.2939983124155396},
    {   -0.9528182145943137,  -0.30354151270840096},
    {   -0.9497352095435054,  -0.31305435910294194},
    {   -0.9465572317631863,   -0.3225359003224504},
    {   -0.9432845990484858,   -0.3319851882207056},
    {   -0.9399176386599484,  -0.34140127787679214},
    {   -0.9364566872908071,  -0.35078322768959114},
    {   -0.9329020910333147,   -0.3601300994719396},
    {   -0.9292542053441347,   -0.3694409585444482},
    {   -0.9255133950087963,  -0.37871487382896885},
    {   -0.9216800341052156,   -0.3879509179417013},
    {   -0.9177545059662885,  -0.39714816728593083},
    {   -0.9137372031415577,  -0.40630570214438755},
    {   -0.9096285273579579,   -0.4154226067712168},
    {   -0.9054288894796434,  -0.42449796948355323},
    {   -0.9011387094669026,   -0.4335308827526885},
    {   -0.8967584163341615,    -0.442520443294823},
    {   -0.8922884481070832,  -0.45146575216139384},
    {   -0.8877292517787654,   -0.4603659148289687},
    {   -0.8830812832650416,   -0.4692200412886977},
    {   -0.8783450073588901,   -0.4780272461353132},
    {   -0.8735208976839544,   -0.4867866486556699},
    {   -0.8686094366471818,   -0.4954973729168152},
    {   -0.8636111153905833,   -0.5041585478535819},
    {   -0.8585264337421193,    -0.512769307355694},
    {   -0.8533559001657175,    -0.521328790354377},
    {   -0.8481000317104267,   -0.5298361409084636},
    {   -0.8427593539587124,    -0.538290508289988},
    {   -0.8373344009738994,   -0.5466910470692574},
    {   -0.8318257152467654,   -0.5550369171993943},
    {   -0.8262338476412924,   -0.5633272841003404},
    {   -0.8205593573395813,   -0.5715613187423143},
    {   -0.8148028117859334,   -0.5797381977287135},
    {    -0.808964786630107,   -0.5878571033784533},
    {   -0.8030458656697526,   -0.5959172238077346},
    {   -0.7970466407920339,   -0.6039177530112312},
    {   -0.7909677119144394,   -0.6118578909426898},
    {   -0.7848096869247909,    -0.619736843594934},
    {    -0.778573181620456,   -0.6275538230792643},
    {   -0.7722588196467677,   -0.6353080477042465},
    {   -0.7658672324346617,   -0.6429987420538799},
    {   -0.7593990591375327,   -0.6506251370651384},
    {   -0.7528549465673204,   -0.6581864701048762},
    {   -0.7462355491298286,   -0.6656819850460903},
    {   -0.7395415287592845,    -0.673110932343533},
    {   -0.7327735548521471,   -0.6804725691086654},
    {   -0.7259323042001671,   -0.6877661591839453},
    {   -0.7190184609227086,   -0.6949909732164435},
    {   -0.7120327163983379,   -0.7021462887307773},
    {    -0.704975769195686,    -0.709231390201358},
    {   -0.6978483250035924,   -0.7162455691239427},
    {   -0.6906510965605368,   -0.7231881240864843},
    {   -0.6833848035833657,    -0.730058360839272},
    {   -0.6760501726953219,   -0.7368555923643557},
    {   -0.6686479373533817,   -0.7435791389442473},
    {   -0.6611788377749109,   -0.7502283282298917},
    {   -0.6536436208636431,   -0.7568024953079012},
    {   -0.6460430401349899,   -0.7633009827670469},
    {   -0.6383778556406909,   -0.7697231407639977},
    {   -0.6306488338928077,    -0.776068327088306},
    {   -0.6228567477870741,   -0.7823359072266267},
    {   -0.6150023765256074,   -0.7885252544261693},
    {   -0.6070865055389884,   -0.7946357497573715},
    {   -0.5991099264077191,   -0.8006667821757921},
    {   -0.5910734367830658,   -0.8066177485832153},
    {   -0.5829778403072937,   -0.8124880538879594},
    {    -0.574823946533304,   -0.8182771110643858},
    {   -0.5666125708436796,   -0.8239843412116011},
    {   -0.5583445343691462,   -0.8296091736113466},
    {   -0.5500206639064614,   -0.8351510457850696},
    {   -0.5416417918357351,   -0.8406094035501709},
    {    -0.533208756037192,   -0.8459837010754229},
    {   -0.5247223998073841,   -0.8512734009355513},
    {   -0.5161835717748627,   -0.8564779741649782},
    {   -0.5075931258153156,    -0.861596900310718},
    {   -0.4989519209661796,   -0.8666296674844217},
    {   -0.4902608213407389,    -0.871575772413566},
    {   -0.4815206960417135,   -0.8764347204917796},
    {   -0.4727324190743498,   -0.8812060258283039},
    {  -0.46389686925902107,   -0.8858892112965813},
    {   -0.4550149301433458,   -0.8904838085819675},
    {   -0.4460874899138341,    -0.894989358228563},
    {  -0.43711544130706936,   -0.8994054096851575},
    {   -0.4280996815204356,   -0.9037315213502856},
    {   -0.4190411121223983,   -0.9079672606163857},
    {   -0.4099406389623485,    -0.912112203913061},
    {   -0.4007991720800186,    -0.916165936749436},
    {   -0.3916176256144788,   -0.9201280537556052},
    {   -0.3823969177127246,   -0.9239981587231696},
    {  -0.37313797043786207,   -0.9277758646448576},
    {   -0.3638417096769031,   -0.9314607937532251},
    {   -0.3545090650481768,   -0.9350525775584321},
    {  -0.34514096980836895,    -0.938550856885091},
    {   -0.3357383607591968,   -0.9419552819081846},
    {   -0.3263021781537297,   -0.9452655121880474},
    {  -0.31683336560236486,   -0.9484812167044101},
    {  -0.30733286997846665,   -0.9516020738895008},
    {  -0.29780164132368053,   -0.9546277716602015},
    {   -0.2882406327529292,   -0.9575580074492568},
    {  -0.27865080035910234,   -0.9603924882355295},
    {   -0.2690331031174478,    -0.963130930573303},
    {    -0.259388502789675,   -0.9657730606206257},
    {  -0.24971796382777964,   -0.9683186141666945},
    {  -0.24002245327759908,   -0.9707673366582761},
    {   -0.2303029406821088,    -0.973118983225162},
    {   -0.2205603979844688,   -0.9753733187046552},
    {  -0.21079579943083007,   -0.9775301176650862},
    {  -0.20101012147291084,   -0.9795891644283565},
    {   -0.1912043426703522,   -0.9815502530915056},
    {  -0.18137944359286293,   -0.9834131875473012},
    {  -0.17153640672216341,   -0.9851777815038505},
    {  -0.16167621635373822,   -0.9868438585032281},
    {  -0.15179985849840735,   -0.9884112519391225},
    {  -0.14190832078372614,   -0.9898798050734964},
    {   -0.1320025923552231,   -0.9912493710522599},
    {   -0.1220836637774863,   -0.9925198129199566},
    {  -0.11215252693510783,   -0.9936910036334584},
    {  -0.10221017493349596,     -0.99476282607467},
    {   -0.0922576019995656,   -0.9957351730622404},
    {  -0.08229580338231637,   -0.9966079473622811},
    {  -0.07232577525330852,   -0.9973810616980894},
    { -0.062348514607046615,    -0.998054438758876},
    { -0.052365019161280925,    -0.998628011207496},
    {  -0.04237628725723648,   -0.9991017216871825},
    {  -0.03238331775977977,   -0.9994755228272822},
    { -0.022387109957533083,   -0.9997493772479927},
    {  -0.01238866346294651,   -0.9999232575641002},
    {-0.0023889781123374934,   -0.9999971463877179},
    {  0.007610946134091949,   -0.9999710363300249},
    {  0.017610109292250417,   -0.9998449300020054},
    {    0.0276075114541547,    -0.999618840014187},
    {   0.03760215288791975,   -0.9992927889753801},
    {  0.047593034137731034,   -0.9988668094904168},
    {   0.05757915612378928,   -0.9983409441568909},
    {    0.0675595202422176,   -0.9977152455608972},
    {   0.07753312846492112,    -0.996989776271774},
    {   0.08749898343938889,   -0.9961646088358458},
    {   0.09745608858842827,   -0.9952398257691683},
    {   0.10740344820982196,   -0.9942155195492777},
    {   0.11734006757589724,   -0.9930917926059423},
    {     0.127264953032998,   -0.9918687573109201},
    {   0.13717711210084924,   -0.9905465359667213},
    {   0.14707555357180424,   -0.9891252607943786},
    {   0.15695928760996464,   -0.9876050739202247},
    {   0.16682732585016302,   -0.9859861273616802},
    {    0.1766786814967987,    -0.984268583012052},
    {   0.18651236942251642,   -0.9824526126243437},
    {   0.19632740626671835,   -0.9805383977940807},
    {   0.20612281053389925,    -0.978526129941151},
    {   0.21589760269179517,   -0.9764160102906628},
    {     0.225650805269336,    -0.974208249852823},
    {   0.23538144295439162,   -0.9719030694018352},
    {   0.24508854269130234,   -0.9695006994538239},
    {   0.25477113377818367,   -0.9670013802437817},
    {    0.2644282479639958,   -0.9644053617015469},
    {   0.27405891954536765,   -0.9617129034268105},
    {    0.2836621854631666,   -0.9589242746631561},
    {   0.29323708539880367,   -0.9560397542711363},
    {   0.30278266187026426,   -0.9530596307003866},
    {    0.3122979603278559,   -0.9499842019607805},
    {   0.32178202924966215,   -0.9468137755926291},
    {   0.33123392023669423,   -0.9435486686359275},
    {      0.34065268810773,   -0.9401892075986501},
    {   0.35003739099383124,   -0.9367357284241014},
    {   0.35938709043253003,   -0.9331885764573206},
    {   0.36870085146167375,   -0.9295481064105487},
    {     0.377977742712921,   -0.9258146823277567},
    {    0.3872168365048774,   -0.9219886775482414},
    {    0.3964172089358629,   -0.9180704746692927},
    {    0.4055779399763014,   -0.9140604655079333},
    {    0.4146981135607228,   -0.9099590510617376},
    {    0.4237768176793687,   -0.9057666414687323},
    {   0.43281314446939284,   -0.9014836559663832},
    {   0.44180619030564644,   -0.8971105228496714},
    {   0.45075505589104015,   -0.8926476794282643},
    {   0.45965884634647264,   -0.8880955719827849},
    {   0.46851667130031827,   -0.8834546557201844},
    {    0.4773276449774631,   -0.8787253947282216},
    {   0.48609088628788194,   -0.8739082619290548},
    {    0.4948055189147464,   -0.8690037390319495},
    {    0.5034706714020559,   -0.8640123164851083},
    {    0.5120854772417827,   -0.8589344934266266},
    {    0.5206490749605218,   -0.8537707776345785},
    {    0.5291606082056376,   -0.8485216854762403},
    {    0.5376192258308986,   -0.8431877418564535},
    {     0.546024081981591,   -0.8377694801651351},
    {    0.5543743361791038,   -0.8322674422239392},
    {    0.5626691534049758,   -0.8266821782320747},
    {    0.5709077041843967,   -0.8210142467112865},
    {     0.579089164669154,   -0.8152642144500036},
    {    0.5872127167200171,   -0.8094326564466602},
    {    0.5952775479885505,    -0.803520155852197},
    {     0.603282851998348,   -0.7975273039117466},
    {    0.6112278282256796,   -0.7914546999055089},
    {    0.6191116821795436,    -0.785302951088824},
    {    0.6269336254811142,   -0.7790726726314472},
    {    0.6346928759425797,   -0.7727644875560322},
    {    0.6423886576453599,     -0.76637902667583},
    {    0.6500202010176978,   -0.7599169285316072},
    {    0.6575867429116155,   -0.7533788393277933},
    {    0.6650875266792291,   -0.7467654128678601},
    {    0.6725218022484126,   -0.7400773104889428},
    {    0.6798888261978043,   -0.7333152009957055},
    {    0.6871878618311483,   -0.7264797605934625},
    {    0.6944181792509638,    -0.719571672820558},
    {    0.7015790554315342,   -0.7125916284800126},
    {    0.7086697742912086,   -0.7055403255704435},
    {    0.7156896267640102,   -0.6984184692162657},
    {    0.7226379108705413,   -0.6912267715971797},
    {    0.7295139317881816,   -0.6839659518769544},
    {    0.7363170019205694,   -0.6766367361315111},
    {    0.7430464409663605,   -0.6692398572763169},
    {    0.7497015759872584,   -0.6617760549930929},
    {    0.7562817414753067,   -0.6542460756558478},
    {    0.7627862794194402,   -0.6466506722562404},
    {    0.7692145393712849,   -0.6389906043282811},
    {    0.7755658785102024,   -0.6312666378723795},
    {    0.7818396617075717,   -0.6234795452787443},
    {    0.7880352615903011,   -0.6156301052501458},
    {    0.7941520586035654,   -0.6077191027240457},
    {    0.8001894410727605,   -0.5997473287941042},
    {    0.8061468052646705,    -0.591715580631071},
    {    0.8120235554478409,   -0.5836246614030692},
    {    0.8178191039521505,   -0.5754753801952796},
    {    0.8235328712275787,   -0.5672685519290316},
    {    0.8291642859021591,   -0.5590049972803128},
    {    0.8347127848391173,   -0.5506855425977021},
    {    0.8401778131931832,   -0.5423110198197346},
    {    0.8455588244660756,   -0.5338822663917095},
    {    0.8508552805611515,   -0.5254001251819458},
    {    0.8560666518372149,   -0.5168654443974957},
    {    0.8611924171614811,   -0.5082790774993257},
    {    0.8662320639616892,  -0.49964188311697016},
    {    0.8711850882773586,  -0.49095472496266984},
    {    0.8760509948101856,   -0.4822184717450008},
    {    0.8808292969735716,   -0.4734339970820047},
    {    0.8855195169412822,  -0.46460217941382737},
    {    0.8901211856952291,   -0.4557239019148759},
    {    0.8946338430723717,   -0.4468000524055015},
    {    0.8990570378107329,   -0.4378315232632188},
    {    0.9033903275945245,   -0.4288192113334681},
    {    0.9076332790983797,   -0.4197640178399322},
    {    0.9117854680306834,   -0.4106668482944145},
    {    0.9158464791760027,   -0.4015286124062887},
    {    0.9198159064366074,   -0.3923502239915282},
    {    0.9236933528730791,    -0.383132600881326},
    {    0.9274784307440054,  -0.37387666483031184},
    {    0.9311707615447533,   -0.3645833414243774},
    {    0.9347699760453199,    -0.355253559988119},
    {    0.9382757143272543,   -0.3458882534919055},
    {    0.9416876258196498,    -0.336488358458582},
    {    0.9450053693342004,   -0.3270548148698187},
    {    0.9482286130993195,  -0.31758856607211317},
    {    0.9513570347933166,   -0.3080905586824567},
    {    0.9543903215766291,   -0.2985617424936733},
    {    0.9573281701231067,  -0.28900307037944106},
    {    0.9601702866503427,    -0.279415498199006},
    {    0.9629163869490529,  -0.26979998470159655},
    {     0.965566196411496,   -0.2601574914305495},
    {    0.9681194500589336,   -0.2504889826271566},
    {    0.9705758925681289,  -0.24079542513424107},
    {     0.972935278296878,  -0.23107778829947434},
    {     0.975197371308574,   -0.2213370438784418},
    {    0.9773619453958009,  -0.21157416593746836},
    {    0.9794287841029539,   -0.2017901307562124},
    {    0.9813976807478845,   -0.1919859167300387},
    {     0.983268438442569,  -0.18216250427217973},
    {    0.9850408701127968,  -0.17232087571569513},
    {    0.9867147985168782,  -0.16246201521523917},
    {    0.9882900562633673,   -0.1525869086486463},
    {    0.9897664858278025,  -0.14269654351834388},
    {    0.9911439395684574,    -0.132791908852603},
    {    0.9924222797411061,  -0.12287399510663644},
    {    0.9936013785127965,  -0.11294379406355384},
    {     0.994681117974634,  -0.10300229873518443},
    {    0.9956613901535722,  -0.09305050326277645},
    {    0.9965420970232102,  -0.08308940281758402},
    {    0.9973231505135948,  -0.07311999350135077},
    {    0.9980044725200279,  -0.06314327224670052},
    {    0.9985859949108766,  -0.05316023671744482},
    {    0.9990676595343865, -0.043171885208817415},
    {    0.9994494182244965, -0.033179216547645586},
    {    0.9997312328056558, -0.023183229992468246},
    {    0.9999130750966412,  -0.01318492513361095},
    {    0.9999949269133749, -0.003185301793227696},
  };

  std::uint32_t indices[sizeof(vertices) / sizeof(vec2) * 3] {0};
  for (int i = 1; i < sizeof(vertices) / sizeof(vec2); i++) {
    indices[i * 3 + 1] = i;
    indices[i * 3 + 2] = i + 1;
  }

  return mr::Prim("default",
                  std::span<vec2>(vertices),
                  std::span<std::uint32_t>(indices),
                  mr::Prim::PrimType::eCircle);
}

mr::Prim mr::create_square() noexcept
{
  using vec2 = float[2];

  vec2 vertices[] = {
    { 0.5f,  0.5f}, // top right
    { 0.5f, -0.5f}, // bottom right
    {-0.5f, -0.5f}, // bottom left
    {-0.5f,  0.5f}, // top left
  };

  unsigned int indices[] = {
    0, 1, 3, // first Triangle
    1, 2, 3  // second Triangle
  };

  return mr::Prim("default",
                  std::span<vec2> {vertices},
                  std::span<unsigned int> {indices},
                  mr::Prim::PrimType::eSquare);
}

std::string mr::serialize(mr::Prim::PrimType ptype, mr::Transform transform) {
  nlohmann::json j;
  j["_ptype"] = ptype;
  j["px"] = transform.posx();
  j["py"] = transform.posy();
  j["a"] = transform.rot();
  j["s"] = transform.scale();
  return j.dump(4);
}
