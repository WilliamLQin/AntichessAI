//
// Created by William Qin on 2022-12-17.
//

// precomputed zobrist pseudo random numbers
unsigned long long int zobrist_rng_white_pawn[64] = {
        0x55e6e46612f693a8, 0xb8432a3ae5954aa4, 0x03f4f1f9a8deee34, 0x27855d90191c8995,
        0xb715fc4d4adde600, 0xaee10a4d477cefed, 0xcbda1ccc3495c2cf, 0xc2120f29480b0bca,
        0x988d7e1d3504b164, 0xbd8df379fdc8357a, 0x54d806a2d6bff761, 0x0853ee51d6ef6197,
        0x8d09346e869b8bb7, 0x4afcbc68e9d4e4be, 0x7a88662f59dd65a4, 0xd189f77d67cb550f,
        0x73d4bf9cc590c475, 0xaa7fe7acc31e475e, 0x39e35c2a8dcaf228, 0x703dd271b4c77c56,
        0xc93df2d0ebf441af, 0x2a14826502f5f011, 0xfefe477cc47b3b77, 0xf95348795a44feff,
        0xdeeb4190323d523a, 0x09dc0ded05124776, 0x20053f83cdb6b74a, 0x52e49c408fde8bf4,
        0xd7901671a57e7f12, 0xc9bfd828e9b99766, 0x9d261730fe3e07fc, 0x6d9b5fb6c6d06787,
        0x1c46aebad4c83ac7, 0x1517a9c739f27379, 0x8e12eb6f0ae00d4c, 0xbbff3c5969211450,
        0x960aaee3185f3ec2, 0x141cdef8590526a5, 0xe9780851d10f33e1, 0xec9dd2c7008bd174,
        0xc7552835cb6cbb20, 0x69952b40babef091, 0x5053b0fe773056cc, 0x83667951e3f2c0d3,
        0xd9b5a89f85ac4507, 0xd2b82347a5b52d21, 0xf06a69958d39cd9c, 0xf2244934d763448b,
        0x3fea877b54b839ba, 0xe7aba5dc5964f4c9, 0xd21e42f907c98f94, 0xa2ae1fda8f78b7d7,
        0x869ffde282625a9d, 0x6400ff4007571223, 0x7e6a1b190d5cebfe, 0x656316eaac2ba4cc,
        0x958220b2bc89de42, 0x8e7ac5e0c5b67cef, 0x977f2d6ee75f21cc, 0x2551a97c988fd72a,
        0xdb050c3de2ed2434, 0x2342c901d66549f0, 0x0f9343d0d969685e, 0x77df15c9cf1f9477,
};

unsigned long long int zobrist_rng_black_pawn[64] = {
        0x2d9bb74e74c4dc6a, 0x1d491a0c5da91111, 0xa550dd4cec1018aa, 0x69a4dec4acd672e4,
        0xec8db46695972a52, 0x01dc697b69670d03, 0x8ba641f7b53a0910, 0x714bb07333c2b163,
        0x15ec66749d4f446e, 0x44694fce899e5ae7, 0x897c75f545a1da32, 0x91dcf7d37012d0fc,
        0xc296f6956b49d483, 0xd28e19b496762360, 0x7689701a2f278f10, 0xa200ce88e96a65ab,
        0xff68165f830c0b33, 0x212becb504e331ba, 0x11cf879f4af8c991, 0x0a7de269cf537ce7,
        0x12bd461637f123c5, 0xcafa4c0eb0cab45b, 0xd8417b579f715472, 0x54aec652f009895e,
        0x5e012a6384f1e8d1, 0xb81cf9a51ed1cc02, 0x11a65289c5717bbc, 0xb415e3ae35961b03,
        0x0dd0aace4d79f5e5, 0xf339e0f240fb3efb, 0x3c4fbf6a529254c4, 0x93961a0f49b94fd8,
        0x5b65d08976593f25, 0x50759b1423d05e6a, 0x6d47488d17a40e6c, 0x2658fa8bd959a547,
        0xe01e4ea6a251bffa, 0xd3b93f1c2e5efba2, 0x9c4443e7124851cd, 0x8bbd8da4d3f77444,
        0xb329beeb43641639, 0x6053a30faddcfbbd, 0x15933b0097dc75ed, 0x663e42dce7d545cf,
        0x821e9a463f28e1cf, 0xa0f3d5af7bb13b2d, 0xdcb727b009232d4c, 0x94eac2f1a21595ad,
        0x00be974fbbe3fe00, 0xe6668dcf194ccff8, 0x5c45027368dc426c, 0x8886f5d8baed258a,
        0xc0972154d6e94040, 0x93c9a80c39ff64cb, 0xb6101b69afde5974, 0x4fa8c7c9c6b404df,
        0x394972ea43b80a88, 0x54052b40fcdffe66, 0x8b61572a1247a713, 0xee209ca9fc86f4cc,
        0xfd13c38fd532e2f9, 0x1dd44dfaf4c78e2a, 0x96a3f71d46c5b9cd, 0xec598d15041918f0,
};

unsigned long long int zobrist_rng_white_knight[64] = {
        0x134ebf6eccb320ef, 0x136600de80a79a20, 0xb3707f4b896d84f8, 0xb962745df844981b,
        0xbf063da8db81e848, 0xa48e855ed76d1331, 0xf466b4b00cf8bcf1, 0xe59e5ce0fc6f034a,
        0xdb1d8cb7ea558cc2, 0xf47257d4ef70f488, 0x4e3ff2f4f02611f9, 0x5f5abda47a83dfe7,
        0x14def87c4e37c2c5, 0x22e59d48a264bdfe, 0x019b34e77d3cafbd, 0x8a895492e588cf33,
        0x90699d19cf658142, 0x16a734cb64bcbb90, 0xe59fae24ea48b3bd, 0x7c68ff663b236b27,
        0xa0235486f6289c59, 0xe00140418ffa7e28, 0x7310f22b4af87143, 0x938544a3b7507fdb,
        0x27133f5ddadfaae7, 0x0848545907f68f20, 0xe0db9459c2d32085, 0x4a2b1b0a695c964c,
        0x9d65d218afc4ca0d, 0xc0da833bd73c7a60, 0xacc000165a7fad92, 0x793437adbd7965d9,
        0x91cbe6c73c29ea93, 0x481bb181936dbb5a, 0xe413c66ef1bf4900, 0x19743952ccd6dcf4,
        0x812a75c4087ea386, 0xbb30c695bab5fd04, 0xdc36d8e2fc64bb39, 0x8e4b93fe8fdc95bd,
        0x53cbf01e5e8778cf, 0xea4a9d3822b0f416, 0x74583f99b7889f8f, 0x39986b1471c3be08,
        0x8359cf39fc09cf00, 0x58c4025d3c1abb10, 0x1e1694d253c17352, 0x5941dee0fafe7101,
        0x0cf69873efa0c261, 0x690a8d3a85b5d76f, 0xaa54519545dc367d, 0x2d83184cebcd7a64,
        0x75a04a0ec8cda626, 0x6ac1e97193f52d65, 0x06aaa3ef5362e114, 0x662f7dfad9310f63,
        0x3c17c489cd1da41b, 0x477795985753ea9b, 0x91339f1c985028be, 0x44241ae06d6d99f5,
        0xaefd137c2144eda8, 0xd7c2499a057f2ae6, 0xeab600362fec4c59, 0x3588c3a0670e602c,
};

unsigned long long int zobrist_rng_black_knight[64] = {
        0x36b1d43753e471a1, 0xaa9bbb7cd1587963, 0xf9fa8b2d36ea0f7b, 0xd6ecca2432e5ce8e,
        0x4aa0f5b4e8cdc804, 0xcb903a43047c9187, 0xa73e2a2f9b5a43a0, 0x5e79419bf29a11ea,
        0x4bce4c00e0f74438, 0xbc8c40329dc045e0, 0x590a094137b2089c, 0xdc69c4365b11c438,
        0x1a763478abfe9cb9, 0x0643266960253ce1, 0x164474d06facc1a2, 0xbc8d67a14f573353,
        0x370ecbecc8a17b5f, 0x6518799af2fe2fda, 0x91da4d13fd726b1b, 0x245007cdb140bb7a,
        0x38b64d567ff890f2, 0x7389e4c55e92e93f, 0x8023ac76386c051e, 0xbbf34e9e295b9b84,
        0x45092decc27d1cf0, 0xc3a03eb503fe9c0a, 0xe82c442bb16eab29, 0x1024172a24207d8d,
        0x5424aeba620192f4, 0xb65b9585d1d5199f, 0x2085f07f6ef479c9, 0x826bf44f75b24a41,
        0x65f1c7004a885ca0, 0x9a799764b0e4a02d, 0x964c7479f770c838, 0xf71850bb84fe1305,
        0xe202a06babd77d8e, 0xf8a90e20ff6aa0b1, 0xffcb3e8eae1da604, 0x7884eab5fa5e90f7,
        0x8c6ff532a648d8c4, 0xf361fab11298d0d7, 0xb26a30ca326d4fef, 0x3b23205136a0f482,
        0xc314a5bcc2a2f120, 0x120efb3471d999e8, 0xf8004f542def4857, 0x913a4b1b89a5d808,
        0x47a1ef63ef0de903, 0x46b78ce7fadcee33, 0x8b8d8b5ba7e14d76, 0x8bbc217fc89a80fe,
        0x44da1d769679c568, 0xa549a05035a11239, 0xc166024ea3ce4d08, 0xa84dc2b575cf5b27,
        0x9c962f0c09899e4f, 0x04628b969eb17ee8, 0xb3b84a93ae434894, 0x49947cca1e6549b5,
        0x915c1edeadb9a9c3, 0x90bdcaf901aa54b0, 0x38c418a08c157b6c, 0xd510d8e5595f89e7,
};

unsigned long long int zobrist_rng_white_bishop[64] = {
        0xe09b58c316712ca6, 0x463b45a26c24618e, 0x2d3581526800efdc, 0x555d5e0d5413e7d1,
        0x83405200cd640a7c, 0xd91d8b361aabe611, 0x8af3145e88193d7c, 0xa4e63d6c40a60c8d,
        0x600d599380f9a11e, 0xad70ea14178d8b7d, 0x75f9e2132d186341, 0xf383394956806fb6,
        0x5d361dfd401d3580, 0x504f52a4548dbe75, 0xb70c88387d696ce1, 0x5513d03ec69f63e2,
        0xf3b271e65f8a8614, 0xe5aac8bf9a57b06e, 0xd6d277cab409ee9e, 0x79a6a63f7466c138,
        0x431dac963b3bf1ab, 0x4cf78c36288b47fd, 0xe3001ac7aaf74e77, 0x2cc8044f4cb7c88c,
        0x713dc32e12defd81, 0x8935c15c88e3ad64, 0xbf71747391d5d05c, 0x378d4b6a1b8b05a0,
        0xeb0f6cc03601645c, 0x19f5b23bb1ade063, 0x30034a20a67fcd19, 0x9f4299c6d9e94e51,
        0x7dd11827d4425e2a, 0x28c06aa683ccf8f2, 0xa1315eb81c2ca839, 0xffa83db34501013a,
        0x68bcf8ca6e82c7c7, 0x056e32c768f8b0b6, 0x5a141cd9bf924135, 0x7bf858daed3d90d9,
        0xbf1daa415b667a8c, 0xf04f96707e366731, 0x8d9abfd98d906e0b, 0x4b30bca5ac3a481a,
        0x09b92c00d728d5ae, 0xfd8d5a636394bfa1, 0x93260254865448b9, 0x24797648da5e2cde,
        0x92413e37f705222a, 0x2baaa4ecb3a52520, 0xf22df038c3abfe5c, 0x725dbb008db81934,
        0x69adec42e20b1c4d, 0xe8a3bcba02d7da6c, 0xee65e32d426b6fb4, 0x352a7d1556b08ae8,
        0x2946bf95e37fab8b, 0xee02d915be4b8643, 0xc9a8d2565dafc345, 0xecec28e21e1f3150,
        0x54bd5ee7146e3b9f, 0xac819b8c1890b07a, 0x31aabdb5e47e6da8, 0xb1fd00f7c753433a,
};

unsigned long long int zobrist_rng_black_bishop[64] = {
        0xa77357f5352a94d1, 0x3a922b967025aa72, 0xca13d93481eaeb22, 0x0dd3bba3c9aa02d2,
        0x88e674615fda8131, 0xbba8edf0b974d103, 0xc0d9fb174d024096, 0xa1ebb7d58a116f1c,
        0x30d528c9d29b5318, 0x6d1804b191244a1a, 0x19fc4a2b249c10cd, 0x5821dfa663d2bb45,
        0x2cda73741f9d2d95, 0xbb041567dc7efe49, 0xb54eb23651cc522b, 0xa23cce486c919d04,
        0x7ef3ebc9d33cf42c, 0x2a5f1ec923d05f0e, 0x206c6c025ce2568c, 0x660ce6159fcc592d,
        0xb8c117a1fa8cb2a7, 0x8ebb492e83013b64, 0x0309246a42e86d13, 0xb8adc9c34252b422,
        0x9e6963ab7dae950a, 0x5cdab92ce3590006, 0xbfa76fde20e887e8, 0x94e60bb303214cf5,
        0xaa13092dca56a116, 0xed1c6f3ce01cd3cc, 0xd98fc77ae84a6e68, 0x27ec394dc2744171,
        0xad54821ece5fd666, 0x78a7ed6ed6d0492a, 0x3051b207aa3f453c, 0xa402aab3a0ce621a,
        0xee9dfe1c96640211, 0xa0a1820e6d733bec, 0x0d9006f58ed3ad78, 0xe8d76298bbf1222c,
        0x5de54afe4169841d, 0x5f21f8768f5f247d, 0x7ed6d17fa17ca7b6, 0xa74148d36ba26ec3,
        0xae7db7b44d03b0e4, 0x4acb3550cf85f935, 0x965d974e4349c850, 0x2923134acfaebce6,
        0xf81541cad8180505, 0x03dd8f4d78b5e590, 0x0c58857c3d3aaa27, 0xf36800a1c51e278a,
        0xd551d2f6d495a4ad, 0xefe55d0a43e4438f, 0x6bcba9243bc8fe7d, 0x087c3ca0aa8403ab,
        0x5ba6a50e00be3873, 0x0d021a3e8a0f2155, 0x8ed30de2104df64c, 0x9bc701c369e71ed2,
        0xf5d960b4e2686c99, 0xd5fe3bfe827d36ef, 0x64592b35ca597b59, 0x7725ac79bdb13f11,
};

unsigned long long int zobrist_rng_white_rook[64] = {
        0x45c4e2f668a5257a, 0x83412586a930265d, 0x8c4c4df091ad9472, 0x4e0e43098f333a32,
        0xccc74c69c171e16c, 0x15aec9f15a6962db, 0x970e66c84c437020, 0xbfc4a343a4c45ee3,
        0xe3e9a4dc4a39842a, 0x033e3b8c59027057, 0x52db1a20e4d58950, 0x44a81d89c5f476f4,
        0x70fc1ed2cf14050c, 0xb7bbecfcf0bdb552, 0x82f8195784c4c477, 0xbacd6a615d3f9475,
        0x54a37e9e077679d3, 0xb3e99d1b1201bbca, 0x6cb6a2e8632072eb, 0x9027f9a778c5477a,
        0x0ad02a202893c124, 0x0ad72e471a5242ee, 0x1a5c6141405d16da, 0x598c497dcab2ce9d,
        0x88f969c975a95b0c, 0x5630381f156b046c, 0xb7d563fb68233be9, 0xf40e35dd6c92534c,
        0xad4143f0c327ab85, 0xc30212ca86d295c2, 0x235ecf282061d201, 0xbc9aafac54881cb6,
        0xa23f774565c58bf7, 0xad96e75a5f4bef4a, 0x09c0272e941de387, 0x868b6b9f6aab8baf,
        0xd67299699bc49dc7, 0xc69602915b923a44, 0x14736045e531c896, 0xc816274133d483bb,
        0xa64d2b9cfd6cae1f, 0xe1ed1dd32e7475c9, 0xd395e3dbcd7693e7, 0xc1f20d0596b6ed03,
        0xc84792bdad44a1d9, 0xe7f3743e3d7cd69e, 0xd00ea2c47099ff9a, 0x226a4390a1250ad2,
        0xff8ad149ed61e566, 0x2958b749d644c08c, 0x854b2377fd7bd08d, 0xf1c458c421e79bfb,
        0xb935b2820573eb48, 0xb30f955498797b1b, 0xa1515ec4267b79af, 0xdb924d6c3322ea19,
        0x01c892c4599202bc, 0x0e58de455ba11fbc, 0x3b2481dda50a5aaa, 0x916017b8e2e8d306,
        0x12978213cd947cac, 0x0b21594becd0b005, 0x4c9b4d710e7a99b7, 0x3ae803d7b0dbfbcd,
};

unsigned long long int zobrist_rng_black_rook[64] = {
        0xd6cebc25ed6d3f8e, 0x10baa774ff50e6c7, 0xc7cf474171c34d03, 0xf8f36d0fc487acec,
        0xc27f0c21bd481f19, 0xd120fc5859d1a76d, 0x621f12ce682e6e32, 0xb8c2040689535266,
        0x1f6d4ad5521bf9bd, 0x7424a86a0955d300, 0x92b7293509b392c8, 0xaedd035850130730,
        0x6ea68fab118c24ae, 0xcda85395ab0c5674, 0x103baea364e01f36, 0x5cffafd5325e1a06,
        0x5c222594a91c2f47, 0x4fb8edf71d437144, 0xe47deef15aa27172, 0x4457f7bac392241d,
        0x93a90ed537927293, 0x6fa2ca22e418f263, 0xf76463176ef04704, 0x0f69f1c7b999a6e8,
        0xa52522b3d864e4eb, 0xcf6253667ea94548, 0xde3777fba7a94a26, 0x7be4aee6327935ba,
        0xe34ef09ab23584f3, 0xe25b9892f8c5bfed, 0x60d0ea47be437712, 0x7aeb43aafd0def22,
        0x0f8b0033824e5c6d, 0x2e40c7eb6d041647, 0x8e9faf113e538a9f, 0x41756c9fdb5d4584,
        0xd9405778f02b7cde, 0x31e48bf6e69ba073, 0x7245ad5517feb6cc, 0x8dc763b88ebe030a,
        0x80aa48ec7028808d, 0xadf3f44aaaa6fac3, 0x0189850179576c1e, 0x8899dcfcf3781ede,
        0x46dffa48447807c4, 0x56adde9b4cd91e54, 0xc41b4523264176d7, 0xf0e22910740a7e71,
        0x281435197ed286b4, 0x26342da00fdd7de7, 0xc5341bd645aff838, 0x8831ad034351cb70,
        0xe4126b5a6055bb2f, 0x4824e1c177678449, 0xfc253abcace308b4, 0xf34cda840f4dacc7,
        0xf3dd019d896200bf, 0xc7db20a025fed108, 0xea49014ce11b3dc4, 0xd5d97d4d9fd64694,
        0xc24a8166b1d1ab80, 0x1b4edb708a346c2d, 0xe892bcd8f05e49da, 0x5572bc4bb9171183,
};

unsigned long long int zobrist_rng_black_queen[64] = {
        0xd2a0e29ac09cc943, 0x6dbf7d59838f1a9e, 0x17897057e5a43915, 0xa899e5204decf444,
        0x63dc6216866fabb6, 0xc57acf40c3eb6fbe, 0x86792b4d339126f3, 0xa027042652c0a2a3,
        0x466ada10bb2a1325, 0x50ce75c41658b24c, 0xfbab0cc6721e4628, 0x0fbaf1dd3206d641,
        0xdb0b6fabd1d2e9bf, 0x67f67a626465f43b, 0x957ff16cd69ef59f, 0x000c53c65a815ce0,
        0xf8972beeb0b3752e, 0x7c9bade2da2dd51d, 0x0315697d246d205a, 0x6d9763376855309c,
        0x3a790ed98c70fb47, 0x6c0a10335ed3db24, 0x7b02600d864d5885, 0xa02912b225dd14b9,
        0x75ad44fb4e60e99e, 0xe86a1a3c2c6ef844, 0x76b77752a6cd291f, 0xcb0dfdbaec1f38aa,
        0xcadf6472b3ba6f7d, 0x0bdf8d0b1b7f61a5, 0x27d967d7679caa1a, 0x229288fef1ff7fc2,
        0xc98dcab9b58d63d3, 0x4af18296be057c0f, 0xa0f21f1dfabe3779, 0x2010eb0ac41b9fa0,
        0x6dedbb77d45a31c3, 0x79b3f8d64d1014bb, 0x62355253be025183, 0x928c1fd708dc130e,
        0xee1afdd9a6554d1d, 0x436ae965b60db0c6, 0x8f4da30e1ad40b87, 0xe40c8f4b222cd765,
        0xddcfbe591558ed9e, 0x34d892dcc76b8e39, 0xfea6456b4e47c6b9, 0x308bbe1ab0d4fe81,
        0xd9e9711b49a1f6dd, 0x0b54082f6707c491, 0xa2dff0b4957d6aa6, 0x0994573a489225d6,
        0x1eefe2e6c0f03315, 0xa3d3eea308d48eef, 0x3f2846792923300e, 0xe2fc6611fa34f47b,
        0xcc08b5c657997bcf, 0x51e9041ccbe21780, 0x9da90c83e0336798, 0x2b8d705d9475d337,
        0xbbe2634da95881f7, 0x3852b8e584429574, 0xb7359f53b1786f2c, 0x377f6460b0cb45d8,
};

unsigned long long int zobrist_rng_white_queen[64] = {
        0xdbe6b9ef75bbc64d, 0x407f5b5c8dda35fe, 0x5a04e39e6bbe1fc9, 0x755fcb0e5ccf51dd,
        0x1482f7361dd68661, 0x55cdf99a5fb208f8, 0xd3852c01431729c3, 0x43940ebdfc7fb1b8,
        0xa3c05b7989ad5a5b, 0x8d3d14b80723b1b9, 0x9f48ae8407e8d468, 0xf9bc08b176cb46e7,
        0xf3f098d47982d659, 0x2e78605d09ecd58f, 0x2c451592b725fd8c, 0xc9ceb491163d9f08,
        0xf1af73ceabc67c87, 0x40f3d78ba7267f34, 0x359308c4758c070d, 0xf46cec2c21b04136,
        0x3c0f1bc10f6a18f1, 0xc0f66af65dcd62c6, 0x3094a230cb56e10d, 0xf6f485bb3a066905,
        0x9a3ecd1adf06fe1e, 0x75425361a8aad557, 0x9dbde73431a2d929, 0xd35240095ef6991e,
        0xf11c835079ba8106, 0x0f351add89a886e7, 0xd66bbea86f39de35, 0xd4cf1da648a7d267,
        0x46f4cd8e52e5387b, 0x9bee5ba850e84837, 0x65b99be7fa79322f, 0x8e8965c4d0053407,
        0xff810031caf2b65a, 0xc1c1977437447272, 0x000910db65344a96, 0x58bec1b5b8afeb23,
        0xfa2a367a4fd42cc2, 0xe1d71eef43b0f151, 0x23426991ce1e9076, 0xc2cf3404199c4afd,
        0xb6c70dd85356648c, 0x6c29f930e1e35fb3, 0xc268fcfe05e93536, 0x99abc711465dd4e7,
        0xb4d091f2d331773f, 0xefee4da6b7a95baf, 0xa98d3f280832dc28, 0xe94b252e7875dc90,
        0xdc5aaf6314a521bc, 0xe078060206277a4a, 0x2b6cdfb69ff83ffa, 0x31db1f8678008f40,
        0x8ac32ae844769f63, 0x1720a638b056b66d, 0x1ea4d8e0c02a42bc, 0xcb7fa65ebcffce80,
        0x1a093afb7e820547, 0xb6f46bc8be8fe8c7, 0xce0383b1077e3783, 0x48193781722577b4,
};

unsigned long long int zobrist_rng_black_king[64] = {
        0xc6cab21469f2a4e8, 0x2cae67b3bb10f59b, 0x400339cac0a102c9, 0x85c4087aacd8f93f,
        0x3000e662dbe8a4b6, 0x640edd905de382e5, 0x19af169af7e836a6, 0x06a23162b9703db7,
        0xd31d7b1c98fd98cf, 0xeeb58502f336a87a, 0x7b23452557197b53, 0x63c171ac6b9e754a,
        0x1698358fd059022f, 0x572d70c1a32a913b, 0x3ec3291b8db7b05a, 0x41dbdc74717c91a9,
        0xf20f649c9352871d, 0xb7e669583f61ce5b, 0x58bb840dd59b059f, 0x818d9c6cdeb303da,
        0xd41d0c08c66f9f43, 0x147666b8a99f72f5, 0x9ecf7a9edb847313, 0x5acb4e05b271db3d,
        0x7ec13572bd613661, 0xc2552f7e5cd6f5b6, 0x2725764a0bbcf070, 0xb1e036a03f3c53cc,
        0x4b2bad58367e40af, 0xe6dd2e743036bbff, 0x57348f1b45a13c2f, 0xa259e8289f84b68c,
        0x31c47f400b33ede6, 0xcff12e683efbaf61, 0x0019549acef32aed, 0xb524e7d76c4605b7,
        0xe649d0035d2d106d, 0x7fd2232a657ccb12, 0x82649271dbba5af6, 0x87f8a0ddd613cafb,
        0x7cf68f3d5367562b, 0xb183d78c06065646, 0xa5b379205ba97d04, 0xc8e44fdaf0eba5b6,
        0xb696e0672b81e8f7, 0x1f9d647ed33f925d, 0xfc338a65d9b118ba, 0x370400ed5d4a2a04,
        0x54a4cf38ab36f512, 0x860ef2e1c1dba510, 0xfab7e4f02753df71, 0x559135add2a5d1ff,
        0x23f3d82a98043d81, 0x7fba218ea4e3547c, 0x041c5b58184eebd9, 0xde78aaf619155aa8,
        0x6a7cdcf4d44e9aeb, 0x065de072a0fba68e, 0x086d59b6f74505d2, 0x2ad76982c1824bc7,
        0x4d186cb5265e2096, 0xd5127985e3a2ec8a, 0x5ff488a5631a6600, 0xa71ab1714c532653,
};

unsigned long long int zobrist_rng_white_king[64] = {
        0xb22559562bccd4b8, 0x6780a67a41b2bed2, 0xc1571db8880ef89c, 0x6c34ae8960826855,
        0x2f37f8deaa1c415c, 0x02953c4fb33ec991, 0x5c92f3dc9dbf2a08, 0x5b2a50484fc47f2b,
        0xc1298d4d8fcc72bf, 0x15567a0d4742bca1, 0xcf43060c1e85ed81, 0x0cf9034f0d49e807,
        0xb913ff501f0b562f, 0x0d1f2139e665b493, 0x08c1a28d43f8762e, 0x097327ab6b9f46ab,
        0xe644b0b747071c85, 0x3f32f2f3f5617885, 0xe7a01a597c39cb25, 0x794ae5d7cd904c40,
        0x4e2456fa986fc093, 0x403eb9ab0e97aecd, 0xf7826c7b4cf4bf64, 0x4532759388b77707,
        0x47c4c78d5c0151b7, 0xb7f658a2667aa325, 0x3bea0bdc042f49cb, 0xbad789b268b66e38,
        0x05cf197d2167f392, 0x7c072c1a93972390, 0x1d0ef2d4524ce498, 0x96ab0ffda3efa252,
        0x6e7a839dba5e5d55, 0x826822d12e321dfb, 0x85bff509ed1fc872, 0x3a796ce6daf9fed4,
        0x1b5ca41e53033b23, 0xf9a92250e6cf6ffc, 0xbaf705da1523d0c0, 0xa3f106ebb0a7071a,
        0xbc64dc87d3e0ac21, 0xf648c225036f309e, 0x76bb78f44cd1c7dd, 0x12ec7ff6c0df08a9,
        0xf2d11e300469058f, 0x08cb0cccc135af17, 0x46be8fb3bb7b395c, 0x157f0704cbb2caf6,
        0x6ff462575869cefe, 0xcbf7521b0e0f73c6, 0xfac7bf3d0899035b, 0x8a969d59111d0f7a,
        0x2ca638c279cb7c52, 0xe290dae573f2860c, 0xfa39646d803bfb38, 0x02c28db2991775b8,
        0x5825319a3444d8f8, 0x5fa7930136ff618e, 0x049352691c93ef23, 0x715625831434be25,
        0x203c1e4518dba4fb, 0x783fb26f3527f2f1, 0x5b18dc9da8d2636a, 0x33f553336c0ca527,
};

unsigned long long int zobrist_rng_turn = 0xfcc1e4356dddf2af;
unsigned long long int zobrist_rng_castling[4] = {
        0xe62c78c0c07373c9, 0x5999fad5869dafae, 0xf2b9d57c20e9fbe5, 0x87054f2bc33b101f,
};
unsigned long long int zobrist_rng_ep[8] = {
        0x3cef9bc42aacaf67, 0x2ab71aca07de61cd, 0x47026881a859b9fd, 0xbb6619696d2759bf,
        0xc33d63a027904f37, 0xddf9aa08c8d33449, 0x27c5ebbb1f779f1d, 0x167f990349a2b7a9,
};

unsigned long long int* zobrist_rng_white_pieces[6] = {
        zobrist_rng_white_pawn,
        zobrist_rng_white_knight,
        zobrist_rng_white_bishop,
        zobrist_rng_white_rook,
        zobrist_rng_white_queen,
        zobrist_rng_white_king
};

unsigned long long int* zobrist_rng_black_pieces[6] = {
        zobrist_rng_black_pawn,
        zobrist_rng_black_knight,
        zobrist_rng_black_bishop,
        zobrist_rng_black_rook,
        zobrist_rng_black_queen,
        zobrist_rng_black_king
};

unsigned long long int** zobrist_rng_pieces[2] = {
        zobrist_rng_black_pieces,
        zobrist_rng_white_pieces
};

unsigned long long int getHashForPieceOnSquare(
    const chess::Color &color,
    const chess::PieceType &piece_type,
    const chess::Square &square
)
{
    return zobrist_rng_pieces[color][piece_type - 1][square];
}

unsigned long long int getHashForSideToMove(const chess::Color &turn)
{
    if (turn == chess::BLACK) {
        return zobrist_rng_turn;
    } else {
        return 0;
    }
}

unsigned long long int getHashForCastlingRights(const chess::Bitboard &castling_rights)
{
    unsigned long long int ret = 0;
    // white
    if (castling_rights & chess::BB_A1) {
        ret ^= zobrist_rng_castling[0];
    }
    if (castling_rights & chess::BB_A8) {
        ret ^= zobrist_rng_castling[1];
    }
    // black
    if (castling_rights & chess::BB_H1) {
        ret ^= zobrist_rng_castling[2];
    }
    if (castling_rights & chess::BB_H8) {
        ret ^= zobrist_rng_castling[3];
    }
    return ret;
}

unsigned long long int getHashForEnPassant(const std::optional<chess::Square> &ep_square)
{
    if (ep_square != std::nullopt) {
        int file = chess::square_file(ep_square.value());
        return zobrist_rng_ep[file];
    }
    return 0;
}
