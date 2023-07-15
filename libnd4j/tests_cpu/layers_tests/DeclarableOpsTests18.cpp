/*
 *  ******************************************************************************
 *  *
 *  *
 *  * This program and the accompanying materials are made available under the
 *  * terms of the Apache License, Version 2.0 which is available at
 *  * https://www.apache.org/licenses/LICENSE-2.0.
 *  *
 *  * See the NOTICE file distributed with this work for additional
 *  * information regarding copyright ownership.
 *  * Unless required by applicable law or agreed to in writing, software
 *  * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  * License for the specific language governing permissions and limitations
 *  * under the License.
 *  *
 *  * SPDX-License-Identifier: Apache-2.0
 *  *****************************************************************************
 */

//
// @author raver119@gmail.com
//
#include <array/NDArray.h>
#include <helpers/GradCheck.h>
#include <ops/declarable/CustomOperations.h>
#include <ops/ops.h>
#include <types/float16.h>
#include <types/bfloat16.h>

#include <array>

#include "testlayers.h"

using namespace sd;

class DeclarableOpsTests18 : public NDArrayTests {
 public:
  DeclarableOpsTests18() {
    printf("\n");
    fflush(stdout);
  }
};

TEST_F(DeclarableOpsTests18, test_bitcast_1) {
  auto x = NDArrayFactory::create<double>(0.23028551377579154);
  auto z = NDArrayFactory::create<sd::LongType>(0);
  auto e = NDArrayFactory::create<sd::LongType>(4597464930322771456L);

  sd::ops::bitcast op;
  auto status = op.execute({&x}, {&z}, {}, {(sd::LongType)sd::DataType::INT64}, {});
  ASSERT_EQ(sd::Status::OK, status);

  ASSERT_EQ(e, z);
}



TEST_F(DeclarableOpsTests18, test_tanh_1) {
  auto x = NDArrayFactory::create<float>('c', {8}, {0.23f, -0.23f, 0.35f, -0.35f, 0.64f, -0.64f, 100000.f, -100000.f});
  auto z = x.ulike();
  auto e = NDArrayFactory::create<float>(
      'c', {8}, {0.226028f, -0.226028f, 0.336376f, -0.336376f, 0.564900f, -0.564900f, 1.f, -1.f});

  sd::ops::tanh op;
  op.execute({&x}, {&z});

  ASSERT_EQ(e, z);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, test_tanh_2) {
  NDArray x('c', {2, 2, 3, 3, 4, 4}, sd::DataType::FLOAT32);
  NDArray z('c', {2, 2, 3, 3, 4, 4}, sd::DataType::FLOAT32);

  x.linspace(-1., 0.003);

  NDArray e(
      'c', {2, 2, 3, 3, 4, 4},
      {-0.761594, -0.760331, -0.759063, -0.757788, -0.756508, -0.755222, -0.753930, -0.752633, -0.751329, -0.750020,
       -0.748704, -0.747383, -0.746056, -0.744723, -0.743383, -0.742038, -0.740687, -0.739330, -0.737967, -0.736598,
       -0.735222, -0.733841, -0.732453, -0.731060, -0.729660, -0.728254, -0.726842, -0.725424, -0.724000, -0.722569,
       -0.721132, -0.719689, -0.718240, -0.716784, -0.715323, -0.713854, -0.712380, -0.710899, -0.709412, -0.707919,
       -0.706419, -0.704913, -0.703401, -0.701882, -0.700357, -0.698825, -0.697287, -0.695742, -0.694191, -0.692634,
       -0.691069, -0.689499, -0.687922, -0.686338, -0.684748, -0.683152, -0.681548, -0.679939, -0.678322, -0.676699,
       -0.675070, -0.673434, -0.671791, -0.670142, -0.668486, -0.666823, -0.665153, -0.663477, -0.661795, -0.660105,
       -0.658409, -0.656706, -0.654997, -0.653280, -0.651557, -0.649827, -0.648091, -0.646348, -0.644597, -0.642841,
       -0.641077, -0.639306, -0.637529, -0.635745, -0.633954, -0.632157, -0.630352, -0.628541, -0.626722, -0.624897,
       -0.623065, -0.621227, -0.619381, -0.617528, -0.615669, -0.613803, -0.611929, -0.610049, -0.608162, -0.606269,
       -0.604368, -0.602460, -0.600546, -0.598624, -0.596696, -0.594760, -0.592818, -0.590869, -0.588913, -0.586950,
       -0.584980, -0.583003, -0.581019, -0.579029, -0.577031, -0.575026, -0.573015, -0.570996, -0.568971, -0.566939,
       -0.564900, -0.562853, -0.560800, -0.558740, -0.556674, -0.554600, -0.552519, -0.550431, -0.548337, -0.546235,
       -0.544127, -0.542012, -0.539890, -0.537761, -0.535625, -0.533482, -0.531332, -0.529176, -0.527013, -0.524842,
       -0.522665, -0.520482, -0.518291, -0.516093, -0.513889, -0.511678, -0.509460, -0.507235, -0.505004, -0.502765,
       -0.500520, -0.498268, -0.496010, -0.493745, -0.491472, -0.489194, -0.486908, -0.484616, -0.482318, -0.480012,
       -0.477700, -0.475381, -0.473056, -0.470724, -0.468385, -0.466040, -0.463689, -0.461330, -0.458966, -0.456594,
       -0.454216, -0.451832, -0.449441, -0.447044, -0.444640, -0.442230, -0.439814, -0.437391, -0.434962, -0.432526,
       -0.430084, -0.427636, -0.425181, -0.422721, -0.420254, -0.417780, -0.415301, -0.412815, -0.410323, -0.407825,
       -0.405321, -0.402811, -0.400295, -0.397773, -0.395244, -0.392710, -0.390170, -0.387623, -0.385071, -0.382513,
       -0.379949, -0.377379, -0.374803, -0.372222, -0.369635, -0.367042, -0.364443, -0.361839, -0.359229, -0.356613,
       -0.353992, -0.351365, -0.348732, -0.346095, -0.343451, -0.340802, -0.338148, -0.335488, -0.332823, -0.330153,
       -0.327477, -0.324796, -0.322110, -0.319419, -0.316723, -0.314021, -0.311314, -0.308602, -0.305886, -0.303164,
       -0.300437, -0.297705, -0.294969, -0.292227, -0.289481, -0.286730, -0.283975, -0.281214, -0.278449, -0.275679,
       -0.272905, -0.270126, -0.267343, -0.264555, -0.261763, -0.258966, -0.256165, -0.253360, -0.250550, -0.247737,
       -0.244919, -0.242097, -0.239270, -0.236440, -0.233606, -0.230768, -0.227925, -0.225079, -0.222229, -0.219376,
       -0.216518, -0.213657, -0.210792, -0.207923, -0.205051, -0.202176, -0.199297, -0.196414, -0.193528, -0.190639,
       -0.187746, -0.184850, -0.181951, -0.179049, -0.176144, -0.173235, -0.170324, -0.167409, -0.164492, -0.161572,
       -0.158649, -0.155723, -0.152794, -0.149863, -0.146929, -0.143992, -0.141053, -0.138112, -0.135168, -0.132221,
       -0.129273, -0.126322, -0.123368, -0.120413, -0.117455, -0.114496, -0.111534, -0.108570, -0.105605, -0.102637,
       -0.099668, -0.096697, -0.093724, -0.090750, -0.087774, -0.084796, -0.081817, -0.078836, -0.075854, -0.072871,
       -0.069886, -0.066900, -0.063913, -0.060924, -0.057935, -0.054945, -0.051953, -0.048961, -0.045968, -0.042974,
       -0.039979, -0.036983, -0.033987, -0.030990, -0.027993, -0.024995, -0.021996, -0.018998, -0.015999, -0.012999,
       -0.010000, -0.007000, -0.004000, -0.001000, 0.002000,  0.005000,  0.008000,  0.011000,  0.013999,  0.016998,
       0.019997,  0.022996,  0.025994,  0.028992,  0.031989,  0.034986,  0.037982,  0.040977,  0.043972,  0.046965,
       0.049958,  0.052950,  0.055942,  0.058932,  0.061921,  0.064909,  0.067895,  0.070881,  0.073865,  0.076848,
       0.079830,  0.082810,  0.085789,  0.088766,  0.091741,  0.094715,  0.097687,  0.100658,  0.103627,  0.106594,
       0.109558,  0.112521,  0.115482,  0.118441,  0.121398,  0.124353,  0.127305,  0.130256,  0.133204,  0.136149,
       0.139092,  0.142033,  0.144971,  0.147907,  0.150840,  0.153771,  0.156698,  0.159623,  0.162545,  0.165465,
       0.168381,  0.171294,  0.174205,  0.177112,  0.180017,  0.182918,  0.185816,  0.188711,  0.191602,  0.194490,
       0.197375,  0.200257,  0.203135,  0.206009,  0.208880,  0.211747,  0.214611,  0.217471,  0.220327,  0.223180,
       0.226028,  0.228873,  0.231714,  0.234551,  0.237384,  0.240213,  0.243038,  0.245858,  0.248675,  0.251487,
       0.254296,  0.257099,  0.259899,  0.262694,  0.265485,  0.268271,  0.271053,  0.273830,  0.276603,  0.279371,
       0.282135,  0.284894,  0.287648,  0.290397,  0.293142,  0.295882,  0.298617,  0.301347,  0.304072,  0.306792,
       0.309507,  0.312217,  0.314922,  0.317622,  0.320317,  0.323006,  0.325691,  0.328370,  0.331044,  0.333712,
       0.336376,  0.339033,  0.341686,  0.344333,  0.346974,  0.349611,  0.352241,  0.354866,  0.357485,  0.360099,
       0.362707,  0.365310,  0.367907,  0.370498,  0.373083,  0.375663,  0.378236,  0.380804,  0.383366,  0.385922,
       0.388473,  0.391017,  0.393555,  0.396088,  0.398614,  0.401134,  0.403649,  0.406157,  0.408659,  0.411155,
       0.413644,  0.416128,  0.418605,  0.421077,  0.423542,  0.426000,  0.428453,  0.430899,  0.433339,  0.435772,
       0.438199,  0.440620,  0.443034,  0.445442,  0.447844,  0.450239,  0.452628,  0.455010,  0.457385,  0.459755,
       0.462117,  0.464473,  0.466823,  0.469166,  0.471502,  0.473832,  0.476155,  0.478471,  0.480781,  0.483085,
       0.485381,  0.487671,  0.489954,  0.492231,  0.494500,  0.496763,  0.499020,  0.501269,  0.503512,  0.505748,
       0.507977,  0.510200,  0.512416,  0.514624,  0.516827,  0.519022,  0.521210,  0.523392,  0.525567,  0.527735,
       0.529896,  0.532050,  0.534197,  0.536338,  0.538471,  0.540598,  0.542718,  0.544831,  0.546937,  0.549036,
       0.551128,  0.553213,  0.555292,  0.557363,  0.559428,  0.561486,  0.563536,  0.565580,  0.567617,  0.569647,
       0.571670,  0.573686,  0.575695,  0.577697,  0.579693,  0.581681,  0.583663,  0.585637,  0.587605,  0.589566,
       0.591519,  0.593466,  0.595406,  0.597339,  0.599265,  0.601184,  0.603097,  0.605002,  0.606901,  0.608792,
       0.610677,  0.612555,  0.614425,  0.616289,  0.618147,  0.619997},
      sd::DataType::FLOAT32);

  sd::ops::tanh op;
  op.execute({&x}, {&z});
  ASSERT_EQ(e, z);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, test_tanh_bp) {
  NDArray x('c', {2, 3, 4}, sd::DataType::FLOAT32);
  NDArray dLdz('c', {2, 3, 4}, sd::DataType::FLOAT32);
  NDArray dLdx('c', {2, 3, 4}, sd::DataType::FLOAT32);

  x.linspace(-1., 0.003);
  dLdz.linspace(0.01, 0.01);

  NDArray e('c', {2, 3, 4}, {0.004200, 0.008438, 0.012715, 0.017030, 0.021385, 0.025778, 0.030211, 0.034684,
                             0.039195, 0.043747, 0.048339, 0.052970, 0.057642, 0.062354, 0.067107, 0.071901,
                             0.076735, 0.081610, 0.086527, 0.091485, 0.096484, 0.101525, 0.106608, 0.111732},
            sd::DataType::FLOAT32);

  sd::ops::tanh_bp op;
  op.execute({&x, &dLdz}, {&dLdx});
  ASSERT_EQ(e, dLdx);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, test_tanh_bp_scalar) {
  NDArray x('c', {2, 3, 4}, sd::DataType::FLOAT32);
  NDArray dLdz = NDArrayFactory::create<float>(7.25f);
  x.linspace(-1., 0.003);

  NDArray exp('c', {2, 3, 4}, {3.0448139, 3.058747,  3.0727215, 3.086736,  3.1007907, 3.1148856, 3.1290195, 3.143194,
                               3.157408,  3.1716602, 3.1859534, 3.2002847, 3.2146554, 3.229064,  3.243512,  3.2579987,
                               3.2725236, 3.2870843, 3.3016858, 3.316324,  3.3309996, 3.345713,  3.3604617, 3.3752484},
              sd::DataType::FLOAT32);

  sd::ops::tanh_bp op;
  auto result = op.evaluate({&x, &dLdz});
  auto dLdxPtr = result.at(0);

  ASSERT_TRUE(dLdxPtr->equalsTo(&exp));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, test_tanh_bp2) {
  NDArray x('f', {2, 3, 4}, sd::DataType::FLOAT32);
  NDArray dLdz('f', {2, 3, 4}, sd::DataType::FLOAT32);
  NDArray dLdx('f', {2, 3, 4}, sd::DataType::FLOAT32);

  x.linspace(-1., 0.003);
  dLdz.linspace(0.01, 0.01);

  NDArray exp('c', {2, 3, 4}, {0.004200, 0.008438, 0.012715, 0.017030, 0.021385, 0.025778, 0.030211, 0.034684,
                               0.039195, 0.043747, 0.048339, 0.052970, 0.057642, 0.062354, 0.067107, 0.071901,
                               0.076735, 0.081610, 0.086527, 0.091485, 0.096484, 0.101525, 0.106608, 0.111732},
              sd::DataType::FLOAT32);
  NDArray e('f', {2, 3, 4}, sd::DataType::FLOAT32);
  e.assign(exp);

  sd::ops::tanh_bp op;
  op.execute({&x, &dLdz}, {&dLdx});
  ASSERT_EQ(e, dLdx);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, test_tanh_bp3) {
  NDArray x('f', {2, 2, 3, 3, 4, 4}, sd::DataType::FLOAT32);
  NDArray dLdz('f', {2, 2, 3, 3, 4, 4}, sd::DataType::FLOAT32);
  NDArray dLdx('f', {2, 2, 3, 3, 4, 4}, sd::DataType::FLOAT32);

  x.linspace(-1.5, 0.005);
  dLdz.linspace(-1., 0.01);

  NDArray exp(
      'c', {2, 2, 3, 3, 4, 4},
      {-0.180707, -0.180525, -0.180324, -0.180103, -0.179861, -0.179599, -0.179315, -0.179009, -0.178682, -0.178333,
       -0.177961, -0.177566, -0.177148, -0.176706, -0.176240, -0.175750, -0.175236, -0.174696, -0.174130, -0.173539,
       -0.172922, -0.172278, -0.171607, -0.170909, -0.170183, -0.169429, -0.168646, -0.167834, -0.166993, -0.166123,
       -0.165222, -0.164290, -0.163327, -0.162334, -0.161308, -0.160250, -0.159159, -0.158035, -0.156877, -0.155686,
       -0.154460, -0.153199, -0.151903, -0.150571, -0.149203, -0.147798, -0.146356, -0.144876, -0.143359, -0.141803,
       -0.140207, -0.138573, -0.136898, -0.135183, -0.133428, -0.131630, -0.129792, -0.127910, -0.125986, -0.124019,
       -0.122008, -0.119953, -0.117853, -0.115708, -0.113517, -0.111279, -0.108996, -0.106665, -0.104286, -0.101859,
       -0.099383, -0.096859, -0.094284, -0.091660, -0.088984, -0.086258, -0.083480, -0.080649, -0.077766, -0.074830,
       -0.071840, -0.068796, -0.065697, -0.062543, -0.059334, -0.056068, -0.052745, -0.049365, -0.045928, -0.042432,
       -0.038878, -0.035264, -0.031591, -0.027858, -0.024064, -0.020209, -0.016292, -0.012313, -0.008272, -0.004168,
       0.000000,  0.004232,  0.008528,  0.012889,  0.017316,  0.021808,  0.026367,  0.030992,  0.035684,  0.040444,
       0.045272,  0.050169,  0.055134,  0.060168,  0.065273,  0.070447,  0.075692,  0.081007,  0.086394,  0.091853,
       0.097383,  0.102986,  0.108662,  0.114411,  0.120233,  0.126129,  0.132099,  0.138144,  0.144263,  0.150457,
       0.156727,  0.163072,  0.169493,  0.175990,  0.182564,  0.189214,  0.195941,  0.202745,  0.209627,  0.216585,
       0.223622,  0.230736,  0.237929,  0.245200,  0.252549,  0.259976,  0.267482,  0.275066,  0.282730,  0.290472,
       0.298293,  0.306193,  0.314172,  0.322230,  0.330366,  0.338582,  0.346877,  0.355250,  0.363703,  0.372234,
       0.380844,  0.389532,  0.398299,  0.407144,  0.416067,  0.425068,  0.434147,  0.443303,  0.452537,  0.461848,
       0.471235,  0.480699,  0.490240,  0.499856,  0.509548,  0.519314,  0.529156,  0.539072,  0.549062,  0.559126,
       0.569262,  0.579471,  0.589753,  0.600106,  0.610530,  0.621024,  0.631588,  0.642222,  0.652924,  0.663694,
       0.674532,  0.685436,  0.696406,  0.707441,  0.718541,  0.729704,  0.740931,  0.752219,  0.763568,  0.774978,
       0.786448,  0.797976,  0.809561,  0.821203,  0.832901,  0.844654,  0.856460,  0.868319,  0.880230,  0.892191,
       0.904201,  0.916260,  0.928366,  0.940518,  0.952715,  0.964955,  0.977238,  0.989561,  1.001925,  1.014327,
       1.026767,  1.039242,  1.051752,  1.064295,  1.076870,  1.089475,  1.102109,  1.114771,  1.127459,  1.140171,
       1.152907,  1.165664,  1.178441,  1.191237,  1.204050,  1.216878,  1.229720,  1.242573,  1.255438,  1.268311,
       1.281192,  1.294078,  1.306968,  1.319860,  1.332753,  1.345644,  1.358533,  1.371417,  1.384294,  1.397163,
       1.410022,  1.422870,  1.435704,  1.448522,  1.461323,  1.474105,  1.486867,  1.499606,  1.512321,  1.525009,
       1.537669,  1.550299,  1.562897,  1.575462,  1.587991,  1.600483,  1.612935,  1.625347,  1.637715,  1.650040,
       1.662317,  1.674545,  1.686724,  1.698850,  1.710922,  1.722939,  1.734897,  1.746797,  1.758635,  1.770409,
       1.782119,  1.793762,  1.805337,  1.816842,  1.828274,  1.839633,  1.850916,  1.862121,  1.873248,  1.884294,
       1.895258,  1.906137,  1.916931,  1.927637,  1.938255,  1.948782,  1.959216,  1.969557,  1.979802,  1.989950,
       2.000000,  2.009950,  2.019798,  2.029543,  2.039184,  2.048719,  2.058147,  2.067466,  2.076675,  2.085773,
       2.094759,  2.103630,  2.112386,  2.121026,  2.129548,  2.137952,  2.146235,  2.154397,  2.162437,  2.170354,
       2.178146,  2.185813,  2.193353,  2.200766,  2.208051,  2.215207,  2.222232,  2.229127,  2.235889,  2.242520,
       2.249017,  2.255379,  2.261607,  2.267699,  2.273656,  2.279475,  2.285158,  2.290702,  2.296108,  2.301376,
       2.306503,  2.311491,  2.316339,  2.321046,  2.325613,  2.330038,  2.334321,  2.338464,  2.342464,  2.346322,
       2.350037,  2.353610,  2.357041,  2.360329,  2.363475,  2.366478,  2.369338,  2.372056,  2.374632,  2.377065,
       2.379356,  2.381505,  2.383512,  2.385378,  2.387103,  2.388686,  2.390128,  2.391431,  2.392593,  2.393615,
       2.394499,  2.395244,  2.395850,  2.396319,  2.396650,  2.396845,  2.396904,  2.396826,  2.396615,  2.396268,
       2.395789,  2.395176,  2.394431,  2.393554,  2.392547,  2.391410,  2.390144,  2.388749,  2.387227,  2.385578,
       2.383804,  2.381904,  2.379880,  2.377734,  2.375465,  2.373075,  2.370565,  2.367936,  2.365188,  2.362324,
       2.359343,  2.356247,  2.353038,  2.349715,  2.346280,  2.342735,  2.339080,  2.335316,  2.331445,  2.327468,
       2.323386,  2.319200,  2.314912,  2.310522,  2.306031,  2.301442,  2.296754,  2.291970,  2.287090,  2.282116,
       2.277049,  2.271890,  2.266641,  2.261302,  2.255876,  2.250362,  2.244763,  2.239080,  2.233314,  2.227467,
       2.221538,  2.215531,  2.209445,  2.203284,  2.197047,  2.190736,  2.184352,  2.177897,  2.171371,  2.164777,
       2.158115,  2.151386,  2.144592,  2.137735,  2.130815,  2.123833,  2.116792,  2.109692,  2.102533,  2.095320,
       2.088051,  2.080727,  2.073352,  2.065925,  2.058447,  2.050921,  2.043347,  2.035727,  2.028061,  2.020351,
       2.012599,  2.004804,  1.996969,  1.989094,  1.981181,  1.973232,  1.965246,  1.957225,  1.949171,  1.941084,
       1.932965,  1.924816,  1.916638,  1.908432,  1.900198,  1.891938,  1.883654,  1.875345,  1.867014,  1.858661,
       1.850286,  1.841892,  1.833479,  1.825048,  1.816600,  1.808136,  1.799657,  1.791165,  1.782659,  1.774141,
       1.765612,  1.757073,  1.748523,  1.739967,  1.731401,  1.722829,  1.714251,  1.705668,  1.697082,  1.688491,
       1.679897,  1.671302,  1.662707,  1.654110,  1.645514,  1.636920,  1.628328,  1.619738,  1.611152,  1.602570,
       1.593993,  1.585422,  1.576857,  1.568299,  1.559749,  1.551207,  1.542674,  1.534151,  1.525638,  1.517136,
       1.508645,  1.500167,  1.491701,  1.483248,  1.474810,  1.466385,  1.457976,  1.449581,  1.441203,  1.432841,
       1.424496,  1.416169,  1.407860,  1.399569,  1.391297,  1.383045,  1.374812,  1.366600,  1.358408,  1.350237,
       1.342088,  1.333961,  1.325856,  1.317774,  1.309715,  1.301679,  1.293668,  1.285680,  1.277718,  1.269780,
       1.261867,  1.253980,  1.246119,  1.238283,  1.230474,  1.222692,  1.214937,  1.207210,  1.199510,  1.191837,
       1.184193,  1.176577,  1.168990,  1.161430,  1.153901,  1.146401,  1.138930,  1.131489,  1.124077,  1.116696,
       1.109345,  1.102024,  1.094734,  1.087475,  1.080246,  1.073049},
      sd::DataType::FLOAT32);

  NDArray e('f', {2, 2, 3, 3, 4, 4}, sd::DataType::FLOAT32);
  e.assign(exp);

  sd::ops::tanh_bp op;
  op.execute({&x, &dLdz}, {&dLdx});
  ASSERT_EQ(e, dLdx);
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, XWPlusB_Bp_1) {
  auto x = NDArrayFactory::create<float>('c', {2, 3}, {1.f, 11.f, 3.f, 14.f, 5.f, 6.f});
  auto w = NDArrayFactory::create<float>('c', {3, 2}, {11.f, 3.f, 4.f, 5.f, 6.f, 2.f});
  auto b = NDArrayFactory::create<float>({100.f, 200.f});

  NDArray dLdz('c', {2, 2}, DataType::FLOAT32);
  dLdz.linspace(1);

  sd::ops::xw_plus_b_bp op;
  auto result = op.evaluate({&x, &w, &b, &dLdz}, {}, {});

  ASSERT_EQ(sd::Status::OK, result.status());

  auto dLdx = result.at(0);
  auto dLdw = result.at(1);
  auto dLdb = result.at(2);

  auto edLdx = NDArrayFactory::create<float>('c', {2, 3}, {17.f, 14.f, 10.f, 45.f, 32.f, 26.f});
  auto edLdw = NDArrayFactory::create<float>('c', {3, 2}, {43.f, 58.f, 26.f, 42.f, 21.f, 30.f});
  auto edLdb = NDArrayFactory::create<float>('c', {2}, {4.f, 6.f});

  ASSERT_TRUE(edLdx.isSameShape(dLdx));
  ASSERT_TRUE(edLdw.isSameShape(dLdw));
  ASSERT_TRUE(edLdb.isSameShape(dLdb));
  ASSERT_TRUE(edLdx.equalsTo(dLdx));
  ASSERT_TRUE(edLdw.equalsTo(dLdw));
  ASSERT_TRUE(edLdb.equalsTo(dLdb));
}
////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, XWPlusB_Bp_2) {
  auto x = NDArrayFactory::create<float>(
      'c', {6, 3}, {1.f, 11.f, 3.f, 14.f, 5.f, 6.f, 1.f, 11.f, 3.f, 14.f, 5.f, 6.f, 1.f, 11.f, 3.f, 14.f, 5.f, 6.f});
  auto w = NDArrayFactory::create<float>('c', {3, 4}, {11.f, 3.f, 4.f, 5.f, 6.f, 2.f, 11.f, 3.f, 4.f, 5.f, 6.f, 2.f});
  auto b = NDArrayFactory::create<float>('c', {4}, {100.f, 200.f, 100.f, 200.f});

  NDArray dLdz('c', {6, 4}, DataType::FLOAT32);
  dLdz.linspace(.1, .5);

  sd::ops::xw_plus_b_bp op;
  auto result = op.evaluate({&x, &w, &b, &dLdz}, {}, {});

  ASSERT_EQ(sd::Status::OK, result.status());

  auto dLdx = result.at(0);
  auto dLdw = result.at(1);
  auto dLdb = result.at(2);

  auto edLdx = NDArrayFactory::create<float>(
      'c', {6, 3},
      {15.3f, 18.700001f, 13.2f, 61.299995f, 62.699997f, 47.200001f, 107.299995f, 106.699997f, 81.199997f, 153.299988f,
       150.699997f, 115.199997f, 199.300018f, 194.700012f, 149.199997f, 245.300018f, 238.700012f, 183.199997f});
  auto edLdw = NDArrayFactory::create<float>('c', {3, 4},
                                             {268.5f, 291.f, 313.5f, 336.f, 226.800003f, 250.800003f, 274.799988f,
                                              298.799988f, 146.699997f, 160.199997f, 173.700012f, 187.200012f});
  auto edLdb = NDArrayFactory::create<float>('c', {4}, {30.6f, 33.599998f, 36.599998f, 39.599998f});
  ASSERT_TRUE(edLdx.isSameShape(dLdx));
  ASSERT_TRUE(edLdw.isSameShape(dLdw));
  ASSERT_TRUE(edLdb.isSameShape(dLdb));
  ASSERT_TRUE(edLdx.equalsTo(dLdx));
  ASSERT_TRUE(edLdw.equalsTo(dLdw));
  ASSERT_TRUE(edLdb.equalsTo(dLdb));
}

////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, XWPlusB_Bp_3) {
  auto x = NDArrayFactory::create<float>('c', {1, 2}, {1.f, 11.f});
  auto w = NDArrayFactory::create<float>('c', {2, 3}, {11.f, 3.f, 4.f, 5.f, 6.f, 2.f});
  auto b = NDArrayFactory::create<float>({100.f, 200.f, 300.f});

  auto dLdz = NDArrayFactory::create<float>('c', {1, 3}, {166.f, 269.f, 326.f});

  sd::ops::xw_plus_b_bp op;
  auto result = op.evaluate({&x, &w, &b, &dLdz}, {}, {});

  ASSERT_EQ(sd::Status::OK, result.status());

  auto dLdx = result.at(0);
  auto dLdw = result.at(1);
  auto dLdb = result.at(2);

  auto edLdx = NDArrayFactory::create<float>('c', {1, 2}, {3937.f, 3096.f});
  auto edLdw = NDArrayFactory::create<float>('c', {2, 3}, {166.f, 269.f, 326.f, 1826.f, 2959.f, 3586.f});
  auto edLdb = NDArrayFactory::create<float>('c', {3}, {166.f, 269.f, 326.f});
  ASSERT_TRUE(edLdx.isSameShape(dLdx));
  ASSERT_TRUE(edLdw.isSameShape(dLdw));
  ASSERT_TRUE(edLdb.isSameShape(dLdb));
  ASSERT_TRUE(edLdx.equalsTo(dLdx));
  ASSERT_TRUE(edLdw.equalsTo(dLdw));
  ASSERT_TRUE(edLdb.equalsTo(dLdb));
}
////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, XWPlusB_Bp_4) {
  auto x = NDArrayFactory::create<float>('c', {1, 2}, {1.f, 11.f});
  auto w = NDArrayFactory::create<float>('c', {2, 1}, {11.f, 3.f});
  auto b = NDArrayFactory::create<float>('c', {1}, {200.f});

  auto dLdz = NDArrayFactory::create<float>('c', {1, 1}, {244.f});

  sd::ops::xw_plus_b_bp op;
  auto result = op.evaluate({&x, &w, &b, &dLdz}, {}, {});

  ASSERT_EQ(sd::Status::OK, result.status());

  auto dLdx = result.at(0);
  auto dLdw = result.at(1);
  auto dLdb = result.at(2);

  auto edLdx = NDArrayFactory::create<float>('c', {1, 2}, {2684.f, 732.f});
  auto edLdw = NDArrayFactory::create<float>('c', {2, 1}, {244.f, 2684.f});
  auto edLdb = NDArrayFactory::create<float>('c', {1}, {244.f});
  ASSERT_TRUE(edLdx.isSameShape(dLdx));
  ASSERT_TRUE(edLdw.isSameShape(dLdw));
  ASSERT_TRUE(edLdb.isSameShape(dLdb));
  ASSERT_TRUE(edLdx.equalsTo(dLdx));
  ASSERT_TRUE(edLdw.equalsTo(dLdw));
  ASSERT_TRUE(edLdb.equalsTo(dLdb));
}
////////////////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, XWPlusB_Bp_5) {
  auto x = NDArrayFactory::create<float>('f', {2, 3}, {1.f, 11.f, 3.f, 14.f, 5.f, 6.f});
  auto w = NDArrayFactory::create<float>('f', {3, 2}, {11.f, 3.f, 4.f, 5.f, 6.f, 2.f});
  auto b = NDArrayFactory::create<float>({100.f, 200.f});

  auto dLdz = NDArrayFactory::create<float>('f', {2, 2}, {140.f, 287.f, 233.f, 351.f});

  sd::ops::xw_plus_b_bp op;
  auto result = op.evaluate({&x, &w, &b, &dLdz}, {}, {});

  ASSERT_EQ(sd::Status::OK, result.status());

  auto dLdx = result.at(0);
  auto dLdw = result.at(1);
  auto dLdb = result.at(2);

  auto edLdxC = NDArrayFactory::create<float>('c', {2, 3}, {2705.f, 1818.f, 1026.f, 4912.f, 2967.f, 1850.f});
  auto edLdwC = NDArrayFactory::create<float>('c', {3, 2}, {3297.f, 4094.f, 4438.f, 5613.f, 2422.f, 3271.f});
  auto edLdbC = NDArrayFactory::create<float>('c', {2}, {427.f, 584.f});

  auto edLdx = NDArrayFactory::create<float>('f', {2, 3});
  auto edLdw = NDArrayFactory::create<float>('f', {3, 2});
  auto edLdb = NDArrayFactory::create<float>('f', {2});

  edLdx.assign(edLdxC);
  edLdw.assign(edLdwC);
  edLdb.assign(edLdbC);

  ASSERT_TRUE(edLdx.isSameShape(dLdx));
  ASSERT_TRUE(edLdw.isSameShape(dLdw));
  ASSERT_TRUE(edLdb.isSameShape(dLdb));
  ASSERT_TRUE(edLdx.equalsTo(dLdx));
  ASSERT_TRUE(edLdw.equalsTo(dLdw));
  ASSERT_TRUE(edLdb.equalsTo(dLdb));
}
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterSgd1) {
  NDArray gradient(
      'c', {1, 5},
      {0.21138794720172882, 0.38947954773902893, 0.2822134494781494, 0.4342866837978363, 0.7928546667098999},
      DataType::FLOAT32);
  auto lr = NDArrayFactory::create<float>(0.001f);

  NDArray update(
      'c', {1, 5},
      {0.00021138794720173, 0.00038947954773903, 0.00028221344947815, 0.00043428668379784, 0.0007928546667099},
      DataType::FLOAT32);

  sd::ops::sgd_updater op;

  sd::Status status = op.execute({&gradient, &lr}, {&gradient}, {}, {});

  ASSERT_EQ(sd::Status::OK, status);
  ASSERT_TRUE(update.equalsTo(gradient));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterSgd2) {
  NDArray gradient(
      'c', {1, 5},
      {0.21138794720172882, 0.38947954773902893, 0.2822134494781494, 0.4342866837978363, 0.7928546667098999},
      DataType::FLOAT32);

  NDArray update(
      'c', {1, 5},
      {0.00021138794720173, 0.00038947954773903, 0.00028221344947815, 0.00043428668379784, 0.0007928546667099},
      DataType::FLOAT32);

  sd::ops::sgd_updater op;

  sd::Status status = op.execute({&gradient}, {&gradient}, {0.001f}, {});
  ASSERT_EQ(sd::Status::OK, status);
  ASSERT_TRUE(update.equalsTo(gradient));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterSgd3) {
  NDArray gradientC(
      'c', {1, 5},
      {0.21138794720172882, 0.38947954773902893, 0.2822134494781494, 0.4342866837978363, 0.7928546667098999},
      DataType::FLOAT32);

  NDArray updateC(
      'c', {1, 5},
      {0.00021138794720173, 0.00038947954773903, 0.00028221344947815, 0.00043428668379784, 0.0007928546667099},
      DataType::FLOAT32);

  NDArray gradient('f', {1, 5}, DataType::FLOAT32);
  NDArray update('f', {1, 5}, DataType::FLOAT32);

  gradient.assign(gradientC);
  update.assign(updateC);

  sd::ops::sgd_updater op;

  auto results = op.evaluate({&gradient}, {0.001f}, {});
  ASSERT_EQ(sd::Status::OK, results.status());
  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterRmsProm1) {
  NDArray grad0('c', {1, 5},
                {0.1811431348323822, 0.10499879717826843, 0.8736756443977356, 0.9707390666007996, 0.7415646314620972},
                DataType::FLOAT32);
  NDArray init('c', {1, 5}, {0.00000001, 0.00000001, 0.00000001, 0.00000001, 0.00000001}, DataType::FLOAT32);

  auto lr = NDArrayFactory::create<float>(0.1f);
  auto decay = NDArrayFactory::create<float>(0.95f);
  auto epsilon = NDArrayFactory::create<float>(1.e-8f);

  sd::ops::rms_prop_updater op;

  sd::Status status = op.execute({&grad0, &init, &lr, &decay, &epsilon}, {&grad0, &init}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);
  NDArray updateExp0(
      'c', {1, 5},
      {0.4472121903197142, 0.4472095514452829, 0.4472135169488324, 0.44721352981195367, 0.44721349127249754},
      DataType::FLOAT32);
  NDArray stateG0(
      'c', {1, 5},
      {0.00164065126484513, 0.00055124687044416, 0.03816546608068996, 0.04711672627124962, 0.02749591463177582},
      DataType::FLOAT32);

  ASSERT_TRUE(grad0.equalsTo(updateExp0));
  ASSERT_TRUE(init.equalsTo(stateG0));

  NDArray grad1('c', {1, 5},
                {0.0139725673943758, 0.19333727657794952, 0.9288347363471985, 0.9253600239753723, 0.3578299283981323},
                DataType::FLOAT32);
  status = op.execute({&grad1, &init, &lr, &decay, &epsilon}, {&grad1, &init}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);
  NDArray updateExp1(
      'c', {1, 5},
      {0.03528177364993147, 0.3952537075263024, 0.32964378302079766, 0.31269398966616074, 0.1984174163852542},
      DataType::FLOAT32);
  NDArray stateG1(
      'c', {1, 5},
      {0.00156838033358239, 0.00239264965265088, 0.07939389114891399, 0.08757544865627226, 0.03252323178305766},
      DataType::FLOAT32);

  ASSERT_TRUE(grad1.equalsTo(updateExp1));
  ASSERT_TRUE(init.equalsTo(stateG1));

  NDArray grad2('c', {1, 5},
                {0.5442887544631958, 0.5386605262756348, 0.884294331073761, 0.15599730610847473, 0.7259345054626465},
                DataType::FLOAT32);
  status = op.execute({&grad2, &init, &lr, &decay, &epsilon}, {&grad2, &init}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);
  NDArray updateExp2(
      'c', {1, 5},
      {0.4262874753567082, 0.41582357367557454, 0.2613066321005825, 0.05369221235564697, 0.3034061716240995},
      DataType::FLOAT32);
  NDArray stateG2(
      'c', {1, 5},
      {0.01630247372865814, 0.01678077529839554, 0.11452301978992785, 0.0844134341991137, 0.05724611550496966},
      DataType::FLOAT32);

  ASSERT_TRUE(grad2.equalsTo(updateExp2));
  ASSERT_TRUE(init.equalsTo(stateG2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterRmsProm2) {
  NDArray grad('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray init('c', {1, 5}, {0.00000001, 0.00000001, 0.00000001, 0.00000001, 0.00000001}, DataType::FLOAT32);

  NDArray update('c', {1, 5}, DataType::FLOAT32);

  sd::ops::rms_prop_updater op;

  sd::Status status = op.execute({&grad, &init}, {&update, &init}, {0.1f, 0.95f, 1.e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);
  NDArray updateExp0(
      'c', {1, 5},
      {0.4472135330146769, 0.44721357487863594, 0.44721358411270346, 0.4472135878446271, 0.447213589800546},
      DataType::FLOAT32);
  NDArray stateG0('c', {1, 5},
                  {0.05000000950000005, 0.2000000095000002, 0.4500000095000004, 0.8000000095000007, 1.250000009500001},
                  DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp0));
  ASSERT_TRUE(init.equalsTo(stateG0));

  status = op.execute({&grad, &init}, {&update, &init}, {0.1f, 0.95f, 1.e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);
  NDArray updateExp1(
      'c', {1, 5},
      {0.32025628253164734, 0.3202562987764395, 0.32025630254446874, 0.3202563041196892, 0.3202563049660074},
      DataType::FLOAT32);
  NDArray stateG1('c', {1, 5},
                  {0.09750000902500008, 0.3900000090250003, 0.8775000090250007, 1.5600000090250012, 2.437500009025002},
                  DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp1));
  ASSERT_TRUE(init.equalsTo(stateG1));

  status = op.execute({&grad, &init}, {&update, &init}, {0.1f, 0.95f, 1.e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);
  NDArray updateExp2(
      'c', {1, 5},
      {0.2647903457769699, 0.2647903552517623, 0.26479035752571606, 0.2647903584968847, 0.2647903590265272},
      DataType::FLOAT32);
  NDArray stateG2('c', {1, 5},
                  {0.1426250085737501, 0.5705000085737504, 1.283625008573751, 2.2820000085737515, 3.565625008573753},
                  DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp2));
  ASSERT_TRUE(init.equalsTo(stateG2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterRmsProm3) {
  NDArray gradC('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initC('c', {1, 5}, {0.00000001, 0.00000001, 0.00000001, 0.00000001, 0.00000001}, DataType::FLOAT32);

  NDArray grad('f', {1, 5}, DataType::FLOAT32);
  NDArray init('f', {1, 5}, DataType::FLOAT32);
  grad.assign(gradC);
  init.assign(initC);

  sd::ops::rms_prop_updater op;
  auto results = op.evaluate({&grad, &init}, {0.1f, 0.95f, 1.e-8}, {});

  NDArray updateC('c', {1, 5},
                  {0.4472135330146769, 0.44721357487863594, 0.44721358411270346, 0.4472135878446271, 0.447213589800546},
                  DataType::FLOAT32);
  NDArray update('f', {1, 5}, DataType::FLOAT32);

  NDArray stateG0C('c', {1, 5},
                   {0.05000000950000005, 0.2000000095000002, 0.4500000095000004, 0.8000000095000007, 1.250000009500001},
                   DataType::FLOAT32);
  NDArray stateG('f', {1, 5}, DataType::FLOAT32);

  update.assign(updateC);
  stateG.assign(stateG0C);

  ASSERT_EQ(sd::Status::OK, results.status());
  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateG.isSameShape(results.at(1)));
  ASSERT_TRUE(stateG.equalsTo(results.at(1)));

  results = op.evaluate({&grad, &stateG}, {0.1f, 0.95f, 1.e-8}, {});
  ASSERT_EQ(sd::Status::OK, results.status());

  NDArray update1C(
      'c', {1, 5},
      {0.32025628253164734, 0.3202562987764395, 0.32025630254446874, 0.3202563041196892, 0.3202563049660074},
      DataType::FLOAT32);
  NDArray stateG1C('c', {1, 5},
                   {0.09750000902500008, 0.3900000090250003, 0.8775000090250007, 1.5600000090250012, 2.437500009025002},
                   DataType::FLOAT32);

  update.assign(update1C);
  stateG.assign(stateG1C);

  ASSERT_EQ(sd::Status::OK, results.status());
  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateG.isSameShape(results.at(1)));
  ASSERT_TRUE(stateG.equalsTo(results.at(1)));

  results = op.evaluate({&grad, &stateG}, {0.1f, 0.95f, 1.e-8}, {});
  ASSERT_EQ(sd::Status::OK, results.status());

  NDArray update2C(
      'c', {1, 5},
      {0.2647903457769699, 0.2647903552517623, 0.26479035752571606, 0.2647903584968847, 0.2647903590265272},
      DataType::FLOAT32);
  NDArray stateG2C('c', {1, 5},
                   {0.1426250085737501, 0.5705000085737504, 1.283625008573751, 2.2820000085737515, 3.565625008573753},
                   DataType::FLOAT32);

  update.assign(update2C);
  stateG.assign(stateG2C);

  ASSERT_EQ(sd::Status::OK, results.status());
  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateG.isSameShape(results.at(1)));
  ASSERT_TRUE(stateG.equalsTo(results.at(1)));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAdaGrad1) {
  // need Java test

  NDArray grad0('c', {1, 5},
                {0.1811431348323822, 0.10499879717826843, 0.8736756443977356, 0.9707390666007996, 0.7415646314620972},
                DataType::FLOAT32);
  NDArray init('c', {1, 5}, {0.00000001, 0.00000001, 0.00000001, 0.00000001, 0.00000001}, DataType::FLOAT32);

  auto lr = NDArrayFactory::create<float>(0.1f);
  auto epsilon = NDArrayFactory::create<float>(1.e-8f);

  sd::ops::ada_grad_updater op;

  sd::Status status = op.execute({&grad0, &init, &lr, &epsilon}, {&grad0, &init}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterNesterovs1) {
  NDArray grad0('c', {1, 5},
                {0.6877592206001282, 0.7830561399459839, 0.7647699117660522, 0.6183066964149475, 0.3303879499435425},
                DataType::FLOAT32);
  NDArray init('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  sd::ops::nesterovs_updater op;

  sd::Status status = op.execute({&grad0, &init}, {&grad0, &init}, {0.1f, 0.9f}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0(
      'c', {1, 5},
      {0.13067425191402435, 0.14878066658973696, 0.14530628323554992, 0.11747827231884002, 0.06277371048927306},
      DataType::FLOAT32);
  NDArray stateV0(
      'c', {1, 5},
      {-0.06877592206001282, -0.0783056139945984, -0.07647699117660522, -0.06183066964149475, -0.03303879499435425},
      DataType::FLOAT32);

  ASSERT_TRUE(grad0.equalsTo(updateExp0));
  ASSERT_TRUE(init.equalsTo(stateV0));

  NDArray grad1('c', {1, 5},
                {0.3676236569881439, 0.07645636051893234, 0.45949840545654297, 0.6335387825965881, 0.2953402101993561},
                DataType::FLOAT32);
  status = op.execute({&grad1, &init}, {&grad1, &init}, {0.1f, 0.9f}, {});
  ASSERT_EQ(sd::Status::OK, status);
  NDArray updateExp1(
      'c', {1, 5},
      {0.12555699169635773, 0.07795425583422186, 0.14925105988979342, 0.17045521110296247, 0.08287606388330458},
      DataType::FLOAT32);
  NDArray stateV1(
      'c', {1, 5},
      {-0.09866069555282593, -0.0781206886470318, -0.11477913260459902, -0.11900148093700408, -0.05926893651485443},
      DataType::FLOAT32);

  ASSERT_TRUE(grad1.equalsTo(updateExp1));
  ASSERT_TRUE(init.equalsTo(stateV1));

  NDArray grad2(
      'c', {1, 5},
      {0.9874004125595093, 0.41817641258239746, 0.16838215291500092, 0.00803728867322206, 0.37015461921691895},
      DataType::FLOAT32);
  status = op.execute({&grad2, &init}, {&grad2, &init}, {0.1f, 0.9f}, {});
  ASSERT_EQ(sd::Status::OK, status);
  NDArray updateExp2(
      'c', {1, 5},
      {0.26752124178409575, 0.1427312761947513, 0.12496370646357537, 0.09791828440688549, 0.11833721622824667},
      DataType::FLOAT32);
  NDArray stateV2(
      'c', {1, 5},
      {-0.18753466725349427, -0.11212626104056837, -0.12013943463563921, -0.10790506171062587, -0.09035750478506088},
      DataType::FLOAT32);

  ASSERT_TRUE(grad2.equalsTo(updateExp2));
  ASSERT_TRUE(init.equalsTo(stateV2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterNesterovs2) {
  NDArray grad('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray init('c', {1, 5}, {0.00000001, 0.00000001, 0.00000001, 0.00000001, 0.00000001}, DataType::FLOAT32);

  NDArray update('c', {1, 5}, DataType::FLOAT32);

  auto lr = NDArrayFactory::create<float>(0.1f);
  auto momentum = NDArrayFactory::create<float>(0.9f);

  sd::ops::nesterovs_updater op;

  sd::Status status = op.execute({&grad, &init, &lr, &momentum}, {&update, &init}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0('c', {1, 5}, {0.19, 0.38, 0.5700000000000001, 0.76, 0.95}, DataType::FLOAT32);
  NDArray stateV0('c', {1, 5}, {-0.1, -0.2, -0.30000000000000004, -0.4, -0.5}, DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp0));
  ASSERT_TRUE(init.equalsTo(stateV0));

  status = op.execute({&grad, &init, &lr, &momentum}, {&update, &init}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);
  NDArray updateExp1('c', {1, 5}, {0.27099999999999996, 0.5419999999999999, 0.813, 1.0839999999999999, 1.355},
                     DataType::FLOAT32);
  NDArray stateV1('c', {1, 5}, {-0.19, -0.38, -0.5700000000000001, -0.76, -0.95}, DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp1));
  ASSERT_TRUE(init.equalsTo(stateV1));

  status = op.execute({&grad, &init, &lr, &momentum}, {&update, &init}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);
  NDArray updateExp2('c', {1, 5}, {0.3439, 0.6878, 1.0317, 1.3756, 1.7195}, DataType::FLOAT32);
  NDArray stateV2('c', {1, 5}, {-0.271, -0.542, -0.8130000000000002, -1.084, -1.355}, DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp2));
  ASSERT_TRUE(init.equalsTo(stateV2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterNesterovs3) {
  NDArray gradC('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initC('c', {1, 5}, {0.00000001, 0.00000001, 0.00000001, 0.00000001, 0.00000001}, DataType::FLOAT32);

  NDArray grad('f', {1, 5}, DataType::FLOAT32);
  NDArray init('f', {1, 5}, DataType::FLOAT32);
  grad.assign(gradC);
  init.assign(initC);

  sd::ops::nesterovs_updater op;
  auto results = op.evaluate({&grad, &init}, {0.1f, 0.9f}, {});

  NDArray updateC('c', {1, 5}, {0.19, 0.38, 0.5700000000000001, 0.76, 0.95}, DataType::FLOAT32);
  NDArray update('f', {1, 5}, DataType::FLOAT32);

  NDArray stateG0C('c', {1, 5}, {-0.1, -0.2, -0.30000000000000004, -0.4, -0.5}, DataType::FLOAT32);
  NDArray stateG('f', {1, 5}, DataType::FLOAT32);

  update.assign(updateC);
  stateG.assign(stateG0C);

  ASSERT_EQ(sd::Status::OK, results.status());
  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateG.isSameShape(results.at(1)));
  ASSERT_TRUE(stateG.equalsTo(results.at(1)));

  results = op.evaluate({&grad, &stateG}, {0.1f, 0.9f}, {});
  ASSERT_EQ(sd::Status::OK, results.status());

  NDArray update1C('c', {1, 5}, {0.27099999999999996, 0.5419999999999999, 0.813, 1.0839999999999999, 1.355},
                   DataType::FLOAT32);
  NDArray stateG1C('c', {1, 5}, {-0.19, -0.38, -0.5700000000000001, -0.76, -0.95}, DataType::FLOAT32);

  update.assign(update1C);
  stateG.assign(stateG1C);

  ASSERT_EQ(sd::Status::OK, results.status());
  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateG.isSameShape(results.at(1)));
  ASSERT_TRUE(stateG.equalsTo(results.at(1)));

  results = op.evaluate({&grad, &stateG}, {0.1f, 0.9f}, {});
  ASSERT_EQ(sd::Status::OK, results.status());

  NDArray update2C('c', {1, 5}, {0.3439, 0.6878, 1.0317, 1.3756, 1.7195}, DataType::FLOAT32);
  NDArray stateG2C('c', {1, 5}, {-0.271, -0.542, -0.8130000000000002, -1.084, -1.355}, DataType::FLOAT32);

  update.assign(update2C);
  stateG.assign(stateG2C);

  ASSERT_EQ(sd::Status::OK, results.status());
  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateG.isSameShape(results.at(1)));
  ASSERT_TRUE(stateG.equalsTo(results.at(1)));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAdaMax1) {
  NDArray grad('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initU('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initM('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  NDArray update('c', {1, 5}, DataType::FLOAT32);

  sd::ops::ada_max_updater op;

  sd::Status status =
      op.execute({&grad, &initU, &initM}, {&update, &initU, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0('c', {1, 5}, {0.001, 0.001, 0.001, 0.001, 0.001}, DataType::FLOAT32);
  NDArray stateU('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray stateM0(
      'c', {1, 5},
      {0.09999999999999998, 0.19999999999999996, 0.29999999999999993, 0.3999999999999999, 0.4999999999999999},
      DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp0));
  ASSERT_TRUE(initU.equalsTo(stateU));
  ASSERT_TRUE(initM.equalsTo(stateM0));

  status = op.execute({&grad, &initU, &initM}, {&update, &initU, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp1('c', {1, 5}, {0.0019, 0.0019, 0.0019, 0.0019, 0.0019}, DataType::FLOAT32);
  NDArray stateM1('c', {1, 5},
                  {0.18999999999999995, 0.3799999999999999, 0.5699999999999998, 0.7599999999999998, 0.9499999999999997},
                  DataType::FLOAT32);
  ASSERT_TRUE(update.equalsTo(updateExp1));
  ASSERT_TRUE(initU.equalsTo(stateU));
  ASSERT_TRUE(initM.equalsTo(stateM1));

  status = op.execute({&grad, &initU, &initM}, {&update, &initU, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp2('c', {1, 5}, {0.00271, 0.00271, 0.00271, 0.00271, 0.00271}, DataType::FLOAT32);
  NDArray stateM2('c', {1, 5},
                  {0.2709999999999999, 0.5419999999999998, 0.8129999999999998, 1.0839999999999996, 1.3549999999999995},
                  DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp2));
  ASSERT_TRUE(initU.equalsTo(stateU));
  ASSERT_TRUE(initM.equalsTo(stateM2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAdaMax2) {
  NDArray grad0('c', {1, 5},
                {0.05387359112501144, 0.9700437784194946, 0.8912011384963989, 0.8891847729682922, 0.18823780119419098},
                DataType::FLOAT32);
  NDArray initU('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initM('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  auto lr = NDArrayFactory::create<float>(0.001f);
  auto beta1 = NDArrayFactory::create<float>(0.9f);
  auto beta2 = NDArrayFactory::create<float>(0.999f);
  auto epsilon = NDArrayFactory::create<float>(1.0e-8);

  sd::ops::ada_max_updater op;

  sd::Status status =
      op.execute({&grad0, &initU, &initM, &lr, &beta1, &beta2, &epsilon}, {&grad0, &initU, &initM}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0('c', {1, 5}, {0.001, 0.001, 0.001, 0.001, 0.001}, DataType::FLOAT32);
  NDArray stateU0(
      'c', {1, 5},
      {0.05387359112501144, 0.9700437784194946, 0.8912011384963989, 0.8891847729682922, 0.18823780119419098},
      DataType::FLOAT32);
  NDArray stateM0(
      'c', {1, 5},
      {0.00538735911250114, 0.09700437784194944, 0.08912011384963987, 0.08891847729682921, 0.01882378011941909},
      DataType::FLOAT32);

  ASSERT_TRUE(grad0.equalsTo(updateExp0));
  ASSERT_TRUE(initU.equalsTo(stateU0));
  ASSERT_TRUE(initM.equalsTo(stateM0));

  NDArray grad1('c', {1, 5},
                {0.6400517821311951, 0.3779360353946686, 0.35128724575042725, 0.6554615497589111, 0.8420050740242004},
                DataType::FLOAT32);

  status = op.execute({&grad1, &initU, &initM, &lr, &beta1, &beta2, &epsilon}, {&grad1, &initU, &initM}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp1(
      'c', {1, 5},
      {0.00107575360832691, 0.00129089809294599, 0.00129546826560191, 0.00163878765669416, 0.00120120308808246},
      DataType::FLOAT32);
  NDArray stateU1('c', {1, 5},
                  {0.6400517821311951, 0.9690737346410752, 0.8903099373579025, 0.888295588195324, 0.8420050740242004},
                  DataType::FLOAT32);
  NDArray stateM1(
      'c', {1, 5},
      {0.06885380141437052, 0.12509754359722136, 0.11533682703971859, 0.1455727845430374, 0.10114190950989721},
      DataType::FLOAT32);

  ASSERT_TRUE(grad1.equalsTo(updateExp1));
  ASSERT_TRUE(initU.equalsTo(stateU1));
  ASSERT_TRUE(initM.equalsTo(stateM1));

  NDArray grad2('c', {1, 5},
                {0.5984494686126709, 0.05978915095329285, 0.5749519467353821, 0.2804091274738312, 0.0192152876406908},
                DataType::FLOAT32);

  status = op.execute({&grad2, &initU, &initM, &lr, &beta1, &beta2, &epsilon}, {&grad2, &initU, &initM}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp2(
      'c', {1, 5},
      {0.00190508497658779, 0.00122473022928962, 0.00181352349370876, 0.00179237223044249, 0.00110500865710834},
      DataType::FLOAT32);
  NDArray stateU2('c', {1, 5},
                  {0.6394117303490638, 0.9681046609064341, 0.8894196274205446, 0.8874072926071286, 0.8411630689501762},
                  DataType::FLOAT32);
  NDArray stateM2(
      'c', {1, 5},
      {0.12181336813420054, 0.11856670433282851, 0.16129833900928492, 0.15905641883611676, 0.09294924732297657},
      DataType::FLOAT32);

  ASSERT_TRUE(grad2.equalsTo(updateExp2));
  ASSERT_TRUE(initU.equalsTo(stateU2));
  ASSERT_TRUE(initM.equalsTo(stateM2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAdaMax3) {
  NDArray gradC('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initVC('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initMC('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  NDArray grad('f', {1, 5}, DataType::FLOAT32);
  NDArray initV('f', {1, 5}, DataType::FLOAT32);
  NDArray initM('f', {1, 5}, DataType::FLOAT32);

  grad.assign(gradC);
  initV.assign(initVC);
  initM.assign(initMC);

  sd::ops::ada_max_updater op;
  auto results = op.evaluate({&grad, &initV, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});

  NDArray updateC('c', {1, 5}, {0.001, 0.001, 0.001, 0.001, 0.001}, DataType::FLOAT32);
  NDArray update('f', {1, 5}, DataType::FLOAT32);

  NDArray stateV0C('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray stateV('f', {1, 5}, DataType::FLOAT32);

  NDArray stateM0C(
      'c', {1, 5},
      {0.09999999999999998, 0.19999999999999996, 0.29999999999999993, 0.3999999999999999, 0.4999999999999999},
      DataType::FLOAT32);
  NDArray stateM('f', {1, 5}, DataType::FLOAT32);

  update.assign(updateC);
  stateV.assign(stateV0C);
  stateM.assign(stateM0C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateV.isSameShape(results.at(1)));
  ASSERT_TRUE(stateV.equalsTo(results.at(1)));
  ASSERT_TRUE(stateM.isSameShape(results.at(2)));
  ASSERT_TRUE(stateM.equalsTo(results.at(2)));

  results = op.evaluate({&grad, &stateV, &stateM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, results.status());

  NDArray update1C('c', {1, 5}, {0.0019, 0.0019, 0.0019, 0.0019, 0.0019}, DataType::FLOAT32);
  NDArray stateM1C(
      'c', {1, 5},
      {0.18999999999999995, 0.3799999999999999, 0.5699999999999998, 0.7599999999999998, 0.9499999999999997},
      DataType::FLOAT32);

  update.assign(update1C);
  stateM.assign(stateM1C);

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateV.isSameShape(results.at(1)));
  ASSERT_TRUE(stateV.equalsTo(results.at(1)));
  ASSERT_TRUE(stateM.isSameShape(results.at(2)));
  ASSERT_TRUE(stateM.equalsTo(results.at(2)));

  results = op.evaluate({&grad, &stateV, &stateM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, results.status());

  NDArray update2C('c', {1, 5}, {0.00271, 0.00271, 0.00271, 0.00271, 0.00271}, DataType::FLOAT32);
  NDArray stateM2C('c', {1, 5},
                   {0.2709999999999999, 0.5419999999999998, 0.8129999999999998, 1.0839999999999996, 1.3549999999999995},
                   DataType::FLOAT32);

  update.assign(update2C);
  stateM.assign(stateM2C);

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateV.isSameShape(results.at(1)));
  ASSERT_TRUE(stateV.equalsTo(results.at(1)));
  ASSERT_TRUE(stateM.isSameShape(results.at(2)));
  ASSERT_TRUE(stateM.equalsTo(results.at(2)));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAdam1) {
  NDArray grad('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initU('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initM('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  NDArray update('c', {1, 5}, DataType::FLOAT32);

  sd::ops::adam_updater op;

  sd::Status status =
      op.execute({&grad, &initU, &initM}, {&update, &initU, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0(
      'c', {1, 5},
      {0.00099999968377233, 0.00099999984188614, 0.00099999989459076, 0.00099999992094306, 0.00099999993675445},
      DataType::FLOAT32);
  NDArray stateV('c', {1, 5}, {0.001, 0.004, 0.00900000000000001, 0.01600000000000001, 0.02500000000000002},
                 DataType::FLOAT32);
  NDArray stateM0(
      'c', {1, 5},
      {0.09999999999999998, 0.19999999999999996, 0.29999999999999993, 0.3999999999999999, 0.4999999999999999},
      DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp0));
  ASSERT_TRUE(initU.equalsTo(stateV));
  ASSERT_TRUE(initM.equalsTo(stateM0));

  status = op.execute({&grad, &initU, &initM}, {&update, &initU, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp1(
      'c', {1, 5},
      {0.00134383858541481, 0.00134383873569809, 0.00134383878579252, 0.00134383881083974, 0.00134383882586807},
      DataType::FLOAT32);
  NDArray stateV1('c', {1, 5},
                  {0.001999, 0.00799600000000001, 0.01799100000000001, 0.03198400000000003, 0.04997500000000005},
                  DataType::FLOAT32);
  NDArray stateM1('c', {1, 5},
                  {0.18999999999999995, 0.3799999999999999, 0.5699999999999998, 0.7599999999999998, 0.9499999999999997},
                  DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp1));
  ASSERT_TRUE(initU.equalsTo(stateV1));
  ASSERT_TRUE(initM.equalsTo(stateM1));

  status = op.execute({&grad, &initU, &initM}, {&update, &initU, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp2(
      'c', {1, 5},
      {0.00156540157923389, 0.00156540172220632, 0.0015654017698638, 0.00156540179369254, 0.00156540180798979},
      DataType::FLOAT32);
  NDArray stateV2('c', {1, 5},
                  {0.002997001, 0.01198800400000001, 0.02697300900000002, 0.04795201600000004, 0.07492502500000006},
                  DataType::FLOAT32);
  NDArray stateM2('c', {1, 5},
                  {0.2709999999999999, 0.5419999999999998, 0.8129999999999998, 1.0839999999999996, 1.3549999999999995},
                  DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp2));
  ASSERT_TRUE(initU.equalsTo(stateV2));
  ASSERT_TRUE(initM.equalsTo(stateM2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAdam2) {
  NDArray grad0('c', {1, 5},
                {0.7124611735343933, 0.7283763289451599, 0.8196553587913513, 0.9501070976257324, 0.2654055953025818},
                DataType::FLOAT32);
  NDArray initU('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initM('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  auto lr = NDArrayFactory::create<float>(0.001f);
  auto beta1 = NDArrayFactory::create<float>(0.9f);
  auto beta2 = NDArrayFactory::create<float>(0.999f);
  auto epsilon = NDArrayFactory::create<float>(1.0e-8);

  sd::ops::adam_updater op;

  sd::Status status =
      op.execute({&grad0, &initU, &initM, &lr, &beta1, &beta2, &epsilon}, {&grad0, &initU, &initM}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0(
      'c', {1, 5},
      {0.00099999955614757, 0.00099999956584582, 0.00099999961419438, 0.0009999996671663, 0.00099999880851273},
      DataType::FLOAT32);
  NDArray stateU0(
      'c', {1, 5},
      {0.00050760092379401, 0.00053053207656763, 0.00067183490719538, 0.00090270349695879, 0.00007044013001792},
      DataType::FLOAT32);
  NDArray stateM0(
      'c', {1, 5},
      {0.07124611735343932, 0.07283763289451597, 0.08196553587913512, 0.09501070976257323, 0.02654055953025817},
      DataType::FLOAT32);

  ASSERT_TRUE(grad0.equalsTo(updateExp0));
  ASSERT_TRUE(initU.equalsTo(stateU0));
  ASSERT_TRUE(initM.equalsTo(stateM0));

  NDArray grad1('c', {1, 5},
                {0.4374369978904724, 0.11488933861255646, 0.6765823364257812, 0.7659900188446045, 0.04410457238554955},
                DataType::FLOAT32);

  status = op.execute({&grad1, &initU, &initM, &lr, &beta1, &beta2, &epsilon}, {&grad1, &initU, &initM}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp1(
      'c', {1, 5},
      {0.00129067017716555, 0.00104532555849556, 0.00133106720937621, 0.00132869584719374, 0.00105226561254395},
      DataType::FLOAT32);
  NDArray stateU1(
      'c', {1, 5},
      {0.00069844444999364, 0.00054320110461789, 0.00112892673025155, 0.00148854150243139, 0.00007231490319321},
      DataType::FLOAT32);
  NDArray stateM1(
      'c', {1, 5},
      {0.10786520540714262, 0.07704280346632002, 0.14142721593379973, 0.16210864067077635, 0.02829696081578731},
      DataType::FLOAT32);

  ASSERT_TRUE(grad1.equalsTo(updateExp1));
  ASSERT_TRUE(initU.equalsTo(stateU1));
  ASSERT_TRUE(initM.equalsTo(stateM1));

  NDArray grad2('c', {1, 5},
                {0.496029257774353, 0.11621368676424026, 0.9112075567245483, 0.5717480182647705, 0.5975669026374817},
                DataType::FLOAT32);

  status = op.execute({&grad2, &initU, &initM, &lr, &beta1, &beta2, &epsilon}, {&grad2, &initU, &initM}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp2(
      'c', {1, 5},
      {0.00150986322036664, 0.00108559662275258, 0.00156079502787382, 0.00150778241516558, 0.00130066803775601},
      DataType::FLOAT32);
  NDArray stateU2(
      'c', {1, 5},
      {0.00094379103011182, 0.00055616352450461, 0.00195809701495322, 0.00181394875731865, 0.00042932879141777},
      DataType::FLOAT32);
  NDArray stateM2(
      'c', {1, 5},
      {0.14668161064386365, 0.08095989179611204, 0.21840525001287456, 0.20307257843017573, 0.08522395499795674},
      DataType::FLOAT32);

  ASSERT_TRUE(grad2.equalsTo(updateExp2));
  ASSERT_TRUE(initU.equalsTo(stateU2));
  ASSERT_TRUE(initM.equalsTo(stateM2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAdam3) {
  NDArray gradC('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initVC('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initMC('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  NDArray grad('f', {1, 5}, DataType::FLOAT32);
  NDArray initV('f', {1, 5}, DataType::FLOAT32);
  NDArray initM('f', {1, 5}, DataType::FLOAT32);

  grad.assign(gradC);
  initV.assign(initVC);
  initM.assign(initMC);

  sd::ops::adam_updater op;
  auto results = op.evaluate({&grad, &initV, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});

  NDArray updateC(
      'c', {1, 5},
      {0.00099999968377233, 0.00099999984188614, 0.00099999989459076, 0.00099999992094306, 0.00099999993675445},
      DataType::FLOAT32);
  NDArray update('f', {1, 5}, DataType::FLOAT32);

  NDArray stateV0C('c', {1, 5}, {0.001, 0.004, 0.00900000000000001, 0.01600000000000001, 0.02500000000000002},
                   DataType::FLOAT32);
  NDArray stateV('f', {1, 5}, DataType::FLOAT32);

  NDArray stateM0C(
      'c', {1, 5},
      {0.09999999999999998, 0.19999999999999996, 0.29999999999999993, 0.3999999999999999, 0.4999999999999999},
      DataType::FLOAT32);
  NDArray stateM('f', {1, 5}, DataType::FLOAT32);

  update.assign(updateC);
  stateV.assign(stateV0C);
  stateM.assign(stateM0C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateV.isSameShape(results.at(1)));
  ASSERT_TRUE(stateV.equalsTo(results.at(1)));
  ASSERT_TRUE(stateM.isSameShape(results.at(2)));
  ASSERT_TRUE(stateM.equalsTo(results.at(2)));

  results = op.evaluate({&grad, &stateV, &stateM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, results.status());

  NDArray update1C(
      'c', {1, 5},
      {0.00134383858541481, 0.00134383873569809, 0.00134383878579252, 0.00134383881083974, 0.00134383882586807},
      DataType::FLOAT32);
  NDArray stateV1C('c', {1, 5},
                   {0.001999, 0.00799600000000001, 0.01799100000000001, 0.03198400000000003, 0.04997500000000005},
                   DataType::FLOAT32);
  NDArray stateM1C(
      'c', {1, 5},
      {0.18999999999999995, 0.3799999999999999, 0.5699999999999998, 0.7599999999999998, 0.9499999999999997},
      DataType::FLOAT32);

  update.assign(update1C);
  stateV.assign(stateV1C);
  stateM.assign(stateM1C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateV.isSameShape(results.at(1)));
  ASSERT_TRUE(stateV.equalsTo(results.at(1)));
  ASSERT_TRUE(stateM.isSameShape(results.at(2)));
  ASSERT_TRUE(stateM.equalsTo(results.at(2)));

  results = op.evaluate({&grad, &stateV, &stateM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});

  NDArray update2C(
      'c', {1, 5},
      {0.00156540157923389, 0.00156540172220632, 0.0015654017698638, 0.00156540179369254, 0.00156540180798979},
      DataType::FLOAT32);
  NDArray stateV2C('c', {1, 5},
                   {0.002997001, 0.01198800400000001, 0.02697300900000002, 0.04795201600000004, 0.07492502500000006},
                   DataType::FLOAT32);
  NDArray stateM2C('c', {1, 5},
                   {0.2709999999999999, 0.5419999999999998, 0.8129999999999998, 1.0839999999999996, 1.3549999999999995},
                   DataType::FLOAT32);

  update.assign(update2C);
  stateV.assign(stateV2C);
  stateM.assign(stateM2C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateV.isSameShape(results.at(1)));
  ASSERT_TRUE(stateV.equalsTo(results.at(1)));
  ASSERT_TRUE(stateM.isSameShape(results.at(2)));
  ASSERT_TRUE(stateM.equalsTo(results.at(2)));
}
//
TEST_F(DeclarableOpsTests18, TestUpdaterAdaBelief1) {
  // here is the python code used for generating test numbers
  // import numpy as np
  // alpha=0.001
  // beta1=0.9
  // beta2=0.999
  // epsilon=1.e-8
  //#https://arxiv.org/pdf/2010.07468.pdf
  // def update( t, w, gradW,   mt, st):
  //        mt =  beta1* mt + (1- beta1)*gradW
  //        st =  beta2* st + (1- beta2)*((gradW-mt)**2) + epsilon
  //        mt_corr =  mt/(1- beta1**t)
  //        st_corr =  st/(1- beta2**t)
  //        upW= alpha*(mt_corr/(np.sqrt(st_corr)+epsilon))
  //        w = w -  upW
  //        return ( w, upW,  mt, st )
  //#if you want to test with more precision np.set_printoptions(precision=9)
  // grad = np.array([1,2,3,4,5], dtype = np.float32)
  // w=np.zeros(5, dtype = np.float32)
  // mt=np.zeros(5, dtype = np.float32)
  // st = np.zeros(5, dtype = np.float32)
  // for t in range(1,4):
  //    w, upW,    mt, st = update(t,w,grad, mt,st )
  //    print(f"---{t}----")
  //    print(f"update {upW}")
  //    print(f" s state {st} ")
  //    print(f" m state {mt} ")

  NDArray grad('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initU('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initM('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  NDArray update('c', {1, 5}, DataType::FLOAT32);

  sd::ops::adabelief_updater op;
  auto t = 0;
  sd::Status status =
      op.execute({&grad, &initU, &initM}, {&update, &initU, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0('c', {1, 5}, {0.0011111f, 0.00111111f, 0.00111111f, 0.00111111f, 0.00111111f}, DataType::FLOAT32);
  NDArray stateV('c', {1, 5}, {0.00081001f, 0.00324001f, 0.00729001f, 0.01296001f, 0.02025001f}, DataType::FLOAT32);
  NDArray stateM0('c', {1, 5}, {0.1f, 0.2f, 0.3f, 0.4f, 0.5f}, DataType::FLOAT32);
  ASSERT_TRUE(update.equalsTo(updateExp0));
  ASSERT_TRUE(initU.equalsTo(stateV));
  ASSERT_TRUE(initM.equalsTo(stateM0));
  t = 1;
  status = op.execute({&grad, &initU, &initM}, {&update, &initU, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {t});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp1('c', {1, 5}, {0.001168f, 0.001168f, 0.001168f, 0.001168f, 0.001168f}, DataType::FLOAT32);
  NDArray stateV1('c', {1, 5}, {0.00146531f, 0.00586118f, 0.01318763f, 0.02344466f, 0.03663227f}, DataType::FLOAT32);
  NDArray stateM1('c', {1, 5}, {0.19f, 0.38f, 0.57000005f, 0.76f, 0.95f}, DataType::FLOAT32);
  ASSERT_TRUE(update.equalsTo(updateExp1));
  ASSERT_TRUE(initU.equalsTo(stateV1));
  ASSERT_TRUE(initM.equalsTo(stateM1));
  t = 2;
  status = op.execute({&grad, &initU, &initM}, {&update, &initU, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {t});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp2('c', {1, 5}, {0.00122557f, 0.00122558f, 0.00122558f, 0.00122558f, 0.00122558f}, DataType::FLOAT32);
  NDArray stateV2('c', {1, 5}, {0.0019953f, 0.00798109f, 0.01795742f, 0.03192428f, 0.04988168f}, DataType::FLOAT32);
  NDArray stateM2('c', {1, 5}, {0.271f, 0.542f, 0.813f, 1.084f, 1.355f}, DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp2));
  ASSERT_TRUE(initU.equalsTo(stateV2));
  ASSERT_TRUE(initM.equalsTo(stateM2));
}

//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAdaDelta1) {
  NDArray grad('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initMsg('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initMsdx('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  NDArray update('c', {1, 5}, DataType::FLOAT32);

  sd::ops::ada_delta_updater op;

  sd_print("About to execute op\n");
  sd::Status status = op.execute({&grad, &initMsg, &initMsdx}, {&update, &initMsg, &initMsdx}, {0.95f, 1.0e-6}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0(
      'c', {1, 5},
      {0.00447209123431084, 0.00447212477470162, 0.00447213098596791, 0.00447213315991723, 0.00447213416614627},
      DataType::FLOAT32);
  NDArray stateMsg0(
      'c', {1, 5},
      {0.05000000000000004, 0.20000000000000018, 0.4500000000000004, 0.8000000000000007, 1.250000000000001},
      DataType::FLOAT32);
  NDArray stateMsdx0('c', {1, 5},
                     {0.0000009999800004, 0.00000099999500002, 0.00000099999777778, 0.00000099999875, 0.0000009999992},
                     DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp0));
  ASSERT_TRUE(initMsg.equalsTo(stateMsg0));
  ASSERT_TRUE(initMsdx.equalsTo(stateMsdx0));

  sd_print("About to execute 2\n");
  status = op.execute({&grad, &initMsg, &initMsdx}, {&update, &initMsg, &initMsdx}, {0.95f, 1.0e-6}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp1(
      'c', {1, 5},
      {0.0045290622655332, 0.00452909666868751, 0.00452910303972733, 0.00452910526959756, 0.00452910630171004},
      DataType::FLOAT32);
  NDArray stateMsg1(
      'c', {1, 5},
      {0.09750000000000009, 0.39000000000000035, 0.8775000000000008, 1.5600000000000014, 2.4375000000000018},
      DataType::FLOAT32);
  NDArray stateMsdx1(
      'c', {1, 5},
      {0.00000197560125063, 0.00000197563108174, 0.00000197563660612, 0.00000197563853966, 0.00000197563943461},
      DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp1));
  ASSERT_TRUE(initMsg.equalsTo(stateMsg1));
  ASSERT_TRUE(initMsdx.equalsTo(stateMsdx1));

  sd_print("About to execute 3\n");
  status = op.execute({&grad, &initMsg, &initMsdx}, {&update, &initMsg, &initMsdx}, {0.95f, 1.0e-6}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp2(
      'c', {1, 5},
      {0.00456759948242601, 0.00456763438748812, 0.00456764085147516, 0.00456764311387702, 0.004567644161047},
      DataType::FLOAT32);
  NDArray stateMsg2('c', {1, 5},
                    {0.1426250000000001, 0.5705000000000005, 1.2836250000000011, 2.282000000000002, 3.5656250000000025},
                    DataType::FLOAT32);
  NDArray stateMsdx2(
      'c', {1, 5},
      {0.0000029199694397, 0.00000292001372254, 0.00000292002192321, 0.00000292002479346, 0.00000292002612198},
      DataType::FLOAT32);

  sd_print("Final assertions\n");
  ASSERT_TRUE(update.equalsTo(updateExp2));
  ASSERT_TRUE(initMsg.equalsTo(stateMsg2));
  ASSERT_TRUE(initMsdx.equalsTo(stateMsdx2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAdaDelta2) {
  NDArray grad0('c', {1, 5},
                {0.22060230374336243, 0.10593396425247192, 0.9027279019355774, 0.831809401512146, 0.2733047902584076},
                DataType::FLOAT32);
  NDArray initMsg('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initMsdx('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  auto rho = NDArrayFactory::create<float>(0.95f);
  auto epsilon = NDArrayFactory::create<float>(1.0e-6);

  sd::ops::ada_delta_updater op;

  sd::Status status = op.execute({&grad0, &initMsg, &initMsdx, &rho, &epsilon}, {&grad0, &initMsg, &initMsdx}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0(
      'c', {1, 5},
      {0.0044712172817412, 0.00446815612502933, 0.00447208107763182, 0.004472071321461, 0.00447153735969189},
      DataType::FLOAT32);
  NDArray stateMsg0(
      'c', {1, 5},
      {0.00243326882084394, 0.0005611002391122, 0.04074588324665051, 0.03459534402219976, 0.00373477541890961},
      DataType::FLOAT32);
  NDArray stateMsdx0(
      'c', {1, 5},
      {0.00000099958919903, 0.00000099822095788, 0.00000099997545825, 0.00000099997109521, 0.00000099973231796},
      DataType::FLOAT32);

  ASSERT_TRUE(grad0.equalsTo(updateExp0));
  ASSERT_TRUE(initMsg.equalsTo(stateMsg0));
  ASSERT_TRUE(initMsdx.equalsTo(stateMsdx0));

  NDArray grad1('c', {1, 5},
                {0.6351608633995056, 0.21878601610660553, 0.6470938920974731, 0.3742971122264862, 0.9453978538513184},
                DataType::FLOAT32);

  status = op.execute({&grad1, &initMsg, &initMsdx, &rho, &epsilon}, {&grad1, &initMsg, &initMsdx}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp1(
      'c', {1, 5},
      {0.00598985959779411, 0.00571609509028959, 0.00374704195122062, 0.00265092283150538, 0.00608704322078556},
      DataType::FLOAT32);
  NDArray stateMsg1(
      'c', {1, 5},
      {0.02248307149952203, 0.00292641126934659, 0.05964511434381081, 0.03987049323214412, 0.0482368917512981},
      DataType::FLOAT32);
  NDArray stateMsdx1(
      'c', {1, 5},
      {0.00000274353063914, 0.00000258199706405, 0.00000165199285454, 0.00000130134213338, 0.00000280235046064},
      DataType::FLOAT32);

  ASSERT_TRUE(grad1.equalsTo(updateExp1));
  ASSERT_TRUE(initMsg.equalsTo(stateMsg1));
  ASSERT_TRUE(initMsdx.equalsTo(stateMsdx1));

  NDArray grad2('c', {1, 5},
                {0.8484492301940918, 0.9634076952934265, 0.6676893830299377, 0.4450211524963379, 0.32364124059677124},
                DataType::FLOAT32);

  status = op.execute({&grad2, &initMsg, &initMsdx, &rho, &epsilon}, {&grad2, &initMsg, &initMsdx}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp2(
      'c', {1, 5},
      {0.00685468722145889, 0.00822128238053265, 0.00386965914609878, 0.00308849888680941, 0.00279277397245112},
      DataType::FLOAT32);
  NDArray stateMsg2(
      'c', {1, 5},
      {0.05735222273539331, 0.04918781007340889, 0.07895331423716523, 0.04777915987899536, 0.05106222979448406},
      DataType::FLOAT32);
  NDArray stateMsdx2(
      'c', {1, 5},
      {0.00000495569095238, 0.00000583237140987, 0.00000231810630717, 0.0000017132162954, 0.00000305221226067},
      DataType::FLOAT32);

  ASSERT_TRUE(grad2.equalsTo(updateExp2));
  ASSERT_TRUE(initMsg.equalsTo(stateMsg2));
  ASSERT_TRUE(initMsdx.equalsTo(stateMsdx2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAdaDelta3) {
  NDArray gradC('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initVC('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);  // Msg
  NDArray initMC('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);  // Msdx

  NDArray grad('f', {1, 5}, DataType::FLOAT32);
  NDArray initMsg('f', {1, 5}, DataType::FLOAT32);
  NDArray initMsdx('f', {1, 5}, DataType::FLOAT32);

  grad.assign(gradC);
  initMsg.assign(initVC);
  initMsdx.assign(initMC);

  sd::ops::ada_delta_updater op;
  auto results = op.evaluate({&grad, &initMsg, &initMsdx}, {0.95f, 1.0e-6}, {});

  NDArray updateC(
      'c', {1, 5},
      {0.00447209123431084, 0.00447212477470162, 0.00447213098596791, 0.00447213315991723, 0.00447213416614627},
      DataType::FLOAT32);
  NDArray update('f', {1, 5}, DataType::FLOAT32);

  NDArray stateV0C(
      'c', {1, 5},
      {0.05000000000000004, 0.20000000000000018, 0.4500000000000004, 0.8000000000000007, 1.250000000000001},
      DataType::FLOAT32);
  NDArray stateMsg('f', {1, 5}, DataType::FLOAT32);

  NDArray stateM0C('c', {1, 5},
                   {0.0000009999800004, 0.00000099999500002, 0.00000099999777778, 0.00000099999875, 0.0000009999992},
                   DataType::FLOAT32);
  NDArray stateMsdx('f', {1, 5}, DataType::FLOAT32);

  update.assign(updateC);
  stateMsg.assign(stateV0C);
  stateMsdx.assign(stateM0C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateMsg.isSameShape(results.at(1)));
  ASSERT_TRUE(stateMsg.equalsTo(results.at(1)));
  ASSERT_TRUE(stateMsdx.isSameShape(results.at(2)));
  ASSERT_TRUE(stateMsdx.equalsTo(results.at(2)));

  results = op.evaluate({&grad, results.at(1), results.at(2)}, {0.95, 1.0e-6}, {});

  NDArray update1C(
      'c', {1, 5},
      {0.0045290622655332, 0.00452909666868751, 0.00452910303972733, 0.00452910526959756, 0.00452910630171004},
      DataType::FLOAT32);

  NDArray stateV1C(
      'c', {1, 5},
      {0.09750000000000009, 0.39000000000000035, 0.8775000000000008, 1.5600000000000014, 2.4375000000000018},
      DataType::FLOAT32);
  NDArray stateM1C(
      'c', {1, 5},
      {0.00000197560125063, 0.00000197563108174, 0.00000197563660612, 0.00000197563853966, 0.00000197563943461},
      DataType::FLOAT32);

  update.assign(update1C);
  stateMsg.assign(stateV1C);
  stateMsdx.assign(stateM1C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateMsg.isSameShape(results.at(1)));
  ASSERT_TRUE(stateMsg.equalsTo(results.at(1)));
  ASSERT_TRUE(stateMsdx.isSameShape(results.at(2)));
  ASSERT_TRUE(stateMsdx.equalsTo(results.at(2)));

  results = op.evaluate({&grad, &stateMsg, &stateMsdx}, {0.95f, 1.0e-6}, {});

  NDArray update2C(
      'c', {1, 5},
      {0.00456759948242601, 0.00456763438748812, 0.00456764085147516, 0.00456764311387702, 0.004567644161047},
      DataType::FLOAT32);
  NDArray stateV2C('c', {1, 5},
                   {0.1426250000000001, 0.5705000000000005, 1.2836250000000011, 2.282000000000002, 3.5656250000000025},
                   DataType::FLOAT32);
  NDArray stateM2C(
      'c', {1, 5},
      {0.0000029199694397, 0.00000292001372254, 0.00000292002192321, 0.00000292002479346, 0.00000292002612198},
      DataType::FLOAT32);

  update.assign(update2C);
  stateMsg.assign(stateV2C);
  stateMsdx.assign(stateM2C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateMsg.isSameShape(results.at(1)));
  ASSERT_TRUE(stateMsg.equalsTo(results.at(1)));
  ASSERT_TRUE(stateMsdx.isSameShape(results.at(2)));
  ASSERT_TRUE(stateMsdx.equalsTo(results.at(2)));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterNadam1) {
  NDArray grad('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initV('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initM('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  NDArray update('c', {1, 5}, DataType::FLOAT32);

  sd::ops::nadam_updater op;

  sd::Status status =
      op.execute({&grad, &initV, &initM}, {&update, &initV, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0(
      'c', {1, 5},
      {0.06008325654320519, 0.06008326604320069, 0.06008326920986652, 0.06008327079319956, 0.0600832717431994},
      DataType::FLOAT32);
  NDArray stateV('c', {1, 5}, {0.001, 0.004, 0.00900000000000001, 0.01600000000000001, 0.02500000000000002},
                 DataType::FLOAT32);
  NDArray stateM0(
      'c', {1, 5},
      {0.09999999999999998, 0.19999999999999996, 0.29999999999999993, 0.3999999999999999, 0.499999999999999},
      DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp0));
  ASSERT_TRUE(initV.equalsTo(stateV));
  ASSERT_TRUE(initM.equalsTo(stateM0));

  status = op.execute({&grad, &initV, &initM}, {&update, &initV, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp1(
      'c', {1, 5},
      {0.06061258367739481, 0.06061259045578174, 0.06061259271524436, 0.06061259384497576, 0.06061259452281461},
      DataType::FLOAT32);
  NDArray stateV1('c', {1, 5},
                  {0.001999, 0.00799600000000001, 0.01799100000000001, 0.03198400000000003, 0.04997500000000005},
                  DataType::FLOAT32);
  NDArray stateM1('c', {1, 5},
                  {0.18999999999999995, 0.3799999999999999, 0.5699999999999998, 0.7599999999999998, 0.9499999999999997},
                  DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp1));
  ASSERT_TRUE(initV.equalsTo(stateV1));
  ASSERT_TRUE(initM.equalsTo(stateM1));

  status = op.execute({&grad, &initV, &initM}, {&update, &initV, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp2(
      'c', {1, 5},
      {0.06281865774973168, 0.06281866348713228, 0.06281866539959938, 0.06281866635583296, 0.06281866692957314},
      DataType::FLOAT32);
  NDArray stateV2('c', {1, 5},
                  {0.002997001, 0.01198800400000001, 0.02697300900000002, 0.04795201600000004, 0.07492502500000006},
                  DataType::FLOAT32);
  NDArray stateM2('c', {1, 5},
                  {0.2709999999999999, 0.5419999999999998, 0.8129999999999998, 1.0839999999999996, 1.3549999999999995},
                  DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp2));
  ASSERT_TRUE(initV.equalsTo(stateV2));
  ASSERT_TRUE(initM.equalsTo(stateM2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterNadam2) {
  NDArray grad0('c', {1, 5},
                {0.8047558665275574, 0.9653639197349548, 0.31240877509117126, 0.9530212879180908, 0.01295729912817478},
                DataType::FLOAT32);
  NDArray initV('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initM('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  auto lr = NDArrayFactory::create<float>(0.001f);
  auto beta1 = NDArrayFactory::create<float>(0.9f);
  auto beta2 = NDArrayFactory::create<float>(0.999f);
  auto epsilon = NDArrayFactory::create<float>(1.0e-8);

  sd::ops::nadam_updater op;

  sd::Status status =
      op.execute({&grad0, &initV, &initM, &lr, &beta1, &beta2, &epsilon}, {&grad0, &initV, &initM}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0(
      'c', {1, 5},
      {0.06008325193356386, 0.0600832558615088, 0.06008321472550684, 0.06008325560661022, 0.0600818092240132},
      DataType::FLOAT32);
  NDArray stateV0(
      'c', {1, 5},
      {0.00064763200471052, 0.00093192749752604, 0.00009759924275397, 0.00090824957522506, 0.0000001678916007},
      DataType::FLOAT32);
  NDArray stateM0(
      'c', {1, 5},
      {0.08047558665275573, 0.09653639197349546, 0.03124087750911712, 0.09530212879180906, 0.00129572991281748},
      DataType::FLOAT32);

  ASSERT_TRUE(grad0.equalsTo(updateExp0));
  ASSERT_TRUE(initV.equalsTo(stateV0));
  ASSERT_TRUE(initM.equalsTo(stateM0));

  NDArray grad1('c', {1, 5},
                {0.9839006662368774, 0.8964805603027344, 0.3631269931793213, 0.00931886397302151, 0.6320028901100159},
                DataType::FLOAT32);

  status = op.execute({&grad1, &initV, &initM, &lr, &beta1, &beta2, &epsilon}, {&grad1, &initV, &initM}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp1(
      'c', {1, 5},
      {0.06273730114378717, 0.0596708938019245, 0.06226533928512862, 0.02621380498466489, 0.06059567064824535},
      DataType::FLOAT32);
  NDArray stateV1(
      'c', {1, 5},
      {0.00161504489372718, 0.00173467296502922, 0.00022936285668667, 0.00090742816687558, 0.0003995953768165},
      DataType::FLOAT32);
  NDArray stateM1(
      'c', {1, 5},
      {0.17081809461116787, 0.17653080880641933, 0.06442948907613753, 0.08670380230993031, 0.06436644593253729},
      DataType::FLOAT32);

  ASSERT_TRUE(grad1.equalsTo(updateExp1));
  ASSERT_TRUE(initV.equalsTo(stateV1));
  ASSERT_TRUE(initM.equalsTo(stateM1));

  NDArray grad2('c', {1, 5},
                {0.7712154984474182, 0.1282273381948471, 0.7019220590591431, 0.8883536458015442, 0.33057701587677},
                DataType::FLOAT32);

  status = op.execute({&grad2, &initV, &initM, &lr, &beta1, &beta2, &epsilon}, {&grad2, &initV, &initM}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp2(
      'c', {1, 5},
      {0.06062658222261493, 0.04001212712739213, 0.06906390273197544, 0.05804376499107734, 0.05097529565845974},
      DataType::FLOAT32);
  NDArray stateV2(
      'c', {1, 5},
      {0.00220820319387896, 0.00174938054232472, 0.00072182807082381, 0.0016956929387176, 0.00050847694486568},
      DataType::FLOAT32);
  NDArray stateM2(
      'c', {1, 5},
      {0.2308578349947929, 0.1717004617452621, 0.12817874607443808, 0.16686878665909166, 0.09098750292696056},
      DataType::FLOAT32);

  ASSERT_TRUE(grad2.equalsTo(updateExp2));
  ASSERT_TRUE(initV.equalsTo(stateV2));
  ASSERT_TRUE(initM.equalsTo(stateM2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterNadam3) {
  NDArray gradC('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initVC('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initMC('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  NDArray grad('f', {1, 5}, DataType::FLOAT32);
  NDArray initV('f', {1, 5}, DataType::FLOAT32);
  NDArray initM('f', {1, 5}, DataType::FLOAT32);

  grad.assign(gradC);
  initV.assign(initVC);
  initM.assign(initMC);

  sd::ops::nadam_updater op;
  auto results = op.evaluate({&grad, &initV, &initM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});

  NDArray updateC(
      'c', {1, 5},
      {0.06008325654320519, 0.06008326604320069, 0.06008326920986652, 0.06008327079319956, 0.0600832717431994},
      DataType::FLOAT32);
  NDArray update('f', {1, 5}, DataType::FLOAT32);

  NDArray stateV0C('c', {1, 5}, {0.001, 0.004, 0.00900000000000001, 0.01600000000000001, 0.02500000000000002},
                   DataType::FLOAT32);
  NDArray stateV('f', {1, 5}, DataType::FLOAT32);

  NDArray stateM0C(
      'c', {1, 5},
      {0.09999999999999998, 0.19999999999999996, 0.29999999999999993, 0.3999999999999999, 0.499999999999999},
      DataType::FLOAT32);
  NDArray stateM('f', {1, 5}, DataType::FLOAT32);

  update.assign(updateC);
  stateV.assign(stateV0C);
  stateM.assign(stateM0C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateV.isSameShape(results.at(1)));
  ASSERT_TRUE(stateV.equalsTo(results.at(1)));
  ASSERT_TRUE(stateM.isSameShape(results.at(2)));
  ASSERT_TRUE(stateM.equalsTo(results.at(2)));

  results = op.evaluate({&grad, &stateV, &stateM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, results.status());

  NDArray update1C(
      'c', {1, 5},
      {0.06061258367739481, 0.06061259045578174, 0.06061259271524436, 0.06061259384497576, 0.06061259452281461},
      DataType::FLOAT32);
  NDArray stateV1C('c', {1, 5},
                   {0.001999, 0.00799600000000001, 0.01799100000000001, 0.03198400000000003, 0.04997500000000005},
                   DataType::FLOAT32);
  NDArray stateM1C(
      'c', {1, 5},
      {0.18999999999999995, 0.3799999999999999, 0.5699999999999998, 0.7599999999999998, 0.9499999999999997},
      DataType::FLOAT32);

  update.assign(update1C);
  stateV.assign(stateV1C);
  stateM.assign(stateM1C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateV.isSameShape(results.at(1)));
  ASSERT_TRUE(stateV.equalsTo(results.at(1)));
  ASSERT_TRUE(stateM.isSameShape(results.at(2)));
  ASSERT_TRUE(stateM.equalsTo(results.at(2)));

  results = op.evaluate({&grad, &stateV, &stateM}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});

  NDArray update2C(
      'c', {1, 5},
      {0.06281865774973168, 0.06281866348713228, 0.06281866539959938, 0.06281866635583296, 0.06281866692957314},
      DataType::FLOAT32);
  NDArray stateV2C('c', {1, 5},
                   {0.002997001, 0.01198800400000001, 0.02697300900000002, 0.04795201600000004, 0.07492502500000006},
                   DataType::FLOAT32);
  NDArray stateM2C('c', {1, 5},
                   {0.2709999999999999, 0.5419999999999998, 0.8129999999999998, 1.0839999999999996, 1.3549999999999995},
                   DataType::FLOAT32);

  update.assign(update2C);
  stateV.assign(stateV2C);
  stateM.assign(stateM2C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateV.isSameShape(results.at(1)));
  ASSERT_TRUE(stateV.equalsTo(results.at(1)));
  ASSERT_TRUE(stateM.isSameShape(results.at(2)));
  ASSERT_TRUE(stateM.equalsTo(results.at(2)));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAmsGrad1) {
  NDArray grad('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initV('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initM('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initH('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  NDArray update('c', {1, 5}, DataType::FLOAT32);

  sd::ops::ams_grad_updater op;

  sd::Status status = op.execute({&grad, &initV, &initM, &initH}, {&update, &initV, &initM, &initH},
                                 {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0(
      'c', {1, 5},
      {0.00099999968377233, 0.00099999984188614, 0.00099999989459076, 0.00099999992094306, 0.00099999993675445},
      DataType::FLOAT32);
  NDArray stateV0('c', {1, 5}, {0.001, 0.004, 0.00900000000000001, 0.01600000000000001, 0.02500000000000002},
                  DataType::FLOAT32);
  NDArray stateH0('c', {1, 5}, {0.001, 0.004, 0.00900000000000001, 0.01600000000000001, 0.02500000000000002},
                  DataType::FLOAT32);
  NDArray stateM0(
      'c', {1, 5},
      {0.09999999999999998, 0.19999999999999996, 0.29999999999999993, 0.3999999999999999, 0.4999999999999999},
      DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp0));
  ASSERT_TRUE(initV.equalsTo(stateV0));
  ASSERT_TRUE(initH.equalsTo(stateH0));
  ASSERT_TRUE(initM.equalsTo(stateM0));

  status = op.execute({&grad, &initV, &initM, &initH}, {&update, &initV, &initM, &initH},
                      {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp1(
      'c', {1, 5},
      {0.00134383858541481, 0.00134383873569809, 0.00134383878579252, 0.00134383881083974, 0.00134383882586807},
      DataType::FLOAT32);
  NDArray stateV1('c', {1, 5},
                  {0.001999, 0.00799600000000001, 0.01799100000000001, 0.03198400000000003, 0.04997500000000005},
                  DataType::FLOAT32);
  NDArray stateH1('c', {1, 5},
                  {0.001999, 0.00799600000000001, 0.01799100000000001, 0.03198400000000003, 0.04997500000000005},
                  DataType::FLOAT32);
  NDArray stateM1('c', {1, 5},
                  {0.18999999999999995, 0.3799999999999999, 0.5699999999999998, 0.7599999999999998, 0.9499999999999997},
                  DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp1));
  ASSERT_TRUE(initV.equalsTo(stateV1));
  ASSERT_TRUE(initH.equalsTo(stateH1));
  ASSERT_TRUE(initM.equalsTo(stateM1));

  status = op.execute({&grad, &initV, &initM, &initH}, {&update, &initV, &initM, &initH},
                      {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp2(
      'c', {1, 5},
      {0.00156540157923389, 0.00156540172220632, 0.0015654017698638, 0.00156540179369254, 0.00156540180798979},
      DataType::FLOAT32);
  NDArray stateV2('c', {1, 5},
                  {0.002997001, 0.01198800400000001, 0.02697300900000002, 0.04795201600000004, 0.07492502500000006},
                  DataType::FLOAT32);
  NDArray stateH2('c', {1, 5},
                  {0.002997001, 0.01198800400000001, 0.02697300900000002, 0.04795201600000004, 0.07492502500000006},
                  DataType::FLOAT32);
  NDArray stateM2('c', {1, 5},
                  {0.2709999999999999, 0.5419999999999998, 0.8129999999999998, 1.0839999999999996, 1.3549999999999995},
                  DataType::FLOAT32);

  ASSERT_TRUE(update.equalsTo(updateExp2));
  ASSERT_TRUE(initV.equalsTo(stateV2));
  ASSERT_TRUE(initH.equalsTo(stateH2));
  ASSERT_TRUE(initM.equalsTo(stateM2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAmsGrad2) {
  NDArray grad0('c', {1, 5},
                {0.5730348229408264, 0.04330538213253021, 0.249028742313385, 0.6514443755149841, 0.7017051577568054},
                DataType::FLOAT32);
  NDArray initH('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initV('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initM('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  auto lr = NDArrayFactory::create<float>(0.001f);
  auto beta1 = NDArrayFactory::create<float>(0.9f);
  auto beta2 = NDArrayFactory::create<float>(0.999f);
  auto epsilon = NDArrayFactory::create<float>(1.0e-8);

  sd::ops::ams_grad_updater op;

  sd::Status status = op.execute({&grad0, &initV, &initM, &initH, &lr, &beta1, &beta2, &epsilon},
                                 {&grad0, &initV, &initM, &initH}, {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp0(
      'c', {1, 5},
      {0.00099999944815292, 0.00099999269777932, 0.00099999873015716, 0.00099999951457465, 0.00099999954934402},
      DataType::FLOAT32);
  NDArray stateV0(
      'c', {1, 5},
      {0.00032836890830282, 0.00000187535612164, 0.00006201531449819, 0.00042437977439011, 0.0004923901284225},
      DataType::FLOAT32);
  NDArray stateH0(
      'c', {1, 5},
      {0.00032836890830282, 0.00000187535612164, 0.00006201531449819, 0.00042437977439011, 0.00049239012842255},
      DataType::FLOAT32);
  NDArray stateM0(
      'c', {1, 5},
      {0.05730348229408263, 0.00433053821325302, 0.0249028742313385, 0.0651444375514984, 0.07017051577568052},
      DataType::FLOAT32);

  ASSERT_TRUE(grad0.equalsTo(updateExp0));
  ASSERT_TRUE(initV.equalsTo(stateV0));
  ASSERT_TRUE(initH.equalsTo(stateH0));
  ASSERT_TRUE(initM.equalsTo(stateM0));

  NDArray grad1('c', {1, 5},
                {0.6404328346252441, 0.9432603120803833, 0.45608729124069214, 0.9097326993942261, 0.748093843460083},
                DataType::FLOAT32);

  status = op.execute({&grad1, &initV, &initM, &initH, &lr, &beta1, &beta2, &epsilon}, {&grad1, &initV, &initM, &initH},
                      {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp1(
      'c', {1, 5},
      {0.00134565543815267, 0.00104022434054697, 0.00130914539820157, 0.00133725290576052, 0.0013453914974122},
      DataType::FLOAT32);
  NDArray stateV1(
      'c', {1, 5},
      {0.00073819475506065, 0.00089161349711151, 0.00026996891641496, 0.00125156897896282, 0.00105154213691696},
      DataType::FLOAT32);
  NDArray stateH1(
      'c', {1, 5},
      {0.00073819475506065, 0.00089161349711151, 0.00026996891641496, 0.00125156897896282, 0.00105154213691696},
      DataType::FLOAT32);
  NDArray stateM1(
      'c', {1, 5},
      {0.11561641752719877, 0.09822351559996603, 0.06802131593227385, 0.14960326373577115, 0.13796284854412078},
      DataType::FLOAT32);

  ASSERT_TRUE(grad1.equalsTo(updateExp1));
  ASSERT_TRUE(initV.equalsTo(stateV1));
  ASSERT_TRUE(initH.equalsTo(stateH1));
  ASSERT_TRUE(initM.equalsTo(stateM1));

  NDArray grad2(
      'c', {1, 5},
      {0.46250319480895996, 0.09698919206857681, 0.21754667162895203, 0.46824514865875244, 0.6005083918571472},
      DataType::FLOAT32);

  status = op.execute({&grad2, &initV, &initM, &initH, &lr, &beta1, &beta2, &epsilon}, {&grad2, &initV, &initM, &initH},
                      {}, {});
  ASSERT_EQ(sd::Status::OK, status);

  NDArray updateExp2(
      'c', {1, 5},
      {0.00154098993679222, 0.00103399135000281, 0.00147364850040774, 0.00149693641196572, 0.00155078467854623},
      DataType::FLOAT32);
  NDArray stateV2(
      'c', {1, 5},
      {0.00095136576551408, 0.00090012878699251, 0.00031702550183538, 0.00146957092922632, 0.0014111009234709},
      DataType::FLOAT32);
  NDArray stateH2(
      'c', {1, 5},
      {0.00095136576551408, 0.00090012878699251, 0.00031702550183538, 0.00146957092922632, 0.0014111009234709},
      DataType::FLOAT32);
  NDArray stateM2(
      'c', {1, 5},
      {0.1503050952553749, 0.09810008324682712, 0.08297385150194167, 0.1814674522280693, 0.1842174028754234},
      DataType::FLOAT32);

  ASSERT_TRUE(grad2.equalsTo(updateExp2));
  ASSERT_TRUE(initV.equalsTo(stateV2));
  ASSERT_TRUE(initH.equalsTo(stateH2));
  ASSERT_TRUE(initM.equalsTo(stateM2));
}
//////////////////////////////////////////////////////////////////////
TEST_F(DeclarableOpsTests18, TestUpdaterAmsGrad3) {
  NDArray gradC('c', {1, 5}, {1, 2, 3, 4, 5}, DataType::FLOAT32);
  NDArray initVC('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initMC('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);
  NDArray initHC('c', {1, 5}, {0.0, 0.0, 0.0, 0.0, 0.0}, DataType::FLOAT32);

  NDArray grad('f', {1, 5}, DataType::FLOAT32);
  NDArray initV('f', {1, 5}, DataType::FLOAT32);
  NDArray initM('f', {1, 5}, DataType::FLOAT32);
  NDArray initH('f', {1, 5}, DataType::FLOAT32);

  grad.assign(gradC);
  initV.assign(initVC);
  initM.assign(initMC);
  initH.assign(initHC);

  sd::ops::ams_grad_updater op;
  auto results = op.evaluate({&grad, &initV, &initM, &initH}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});

  NDArray updateC(
      'c', {1, 5},
      {0.00099999968377233, 0.00099999984188614, 0.00099999989459076, 0.00099999992094306, 0.00099999993675445},
      DataType::FLOAT32);
  NDArray update('f', {1, 5}, DataType::FLOAT32);

  NDArray stateV0C('c', {1, 5}, {0.001, 0.004, 0.00900000000000001, 0.01600000000000001, 0.02500000000000002},
                   DataType::FLOAT32);
  NDArray stateV('f', {1, 5}, DataType::FLOAT32);

  NDArray stateM0C(
      'c', {1, 5},
      {0.09999999999999998, 0.19999999999999996, 0.29999999999999993, 0.3999999999999999, 0.4999999999999999},
      DataType::FLOAT32);
  NDArray stateM('f', {1, 5}, DataType::FLOAT32);

  NDArray stateH0C('c', {1, 5}, {0.001, 0.004, 0.00900000000000001, 0.01600000000000001, 0.02500000000000002},
                   DataType::FLOAT32);
  NDArray stateH('f', {1, 5}, DataType::FLOAT32);

  update.assign(updateC);
  stateV.assign(stateV0C);
  stateM.assign(stateM0C);
  stateH.assign(stateH0C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateV.isSameShape(results.at(1)));
  ASSERT_TRUE(stateV.equalsTo(results.at(1)));
  ASSERT_TRUE(stateM.isSameShape(results.at(2)));
  ASSERT_TRUE(stateM.equalsTo(results.at(2)));
  ASSERT_TRUE(stateH.isSameShape(results.at(3)));
  ASSERT_TRUE(stateH.equalsTo(results.at(3)));

  results = op.evaluate({&grad, &stateV, &stateM, &stateH}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});
  ASSERT_EQ(sd::Status::OK, results.status());

  NDArray update1C(
      'c', {1, 5},
      {0.00134383858541481, 0.00134383873569809, 0.00134383878579252, 0.00134383881083974, 0.00134383882586807},
      DataType::FLOAT32);
  NDArray stateV1C('c', {1, 5},
                   {0.001999, 0.00799600000000001, 0.01799100000000001, 0.03198400000000003, 0.04997500000000005},
                   DataType::FLOAT32);
  NDArray stateM1C(
      'c', {1, 5},
      {0.18999999999999995, 0.3799999999999999, 0.5699999999999998, 0.7599999999999998, 0.9499999999999997},
      DataType::FLOAT32);
  NDArray stateH1C('c', {1, 5},
                   {0.001999, 0.00799600000000001, 0.01799100000000001, 0.03198400000000003, 0.04997500000000005},
                   DataType::FLOAT32);

  update.assign(update1C);
  stateV.assign(stateV1C);
  stateM.assign(stateM1C);
  stateH.assign(stateH1C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateV.isSameShape(results.at(1)));
  ASSERT_TRUE(stateV.equalsTo(results.at(1)));
  ASSERT_TRUE(stateM.isSameShape(results.at(2)));
  ASSERT_TRUE(stateM.equalsTo(results.at(2)));
  ASSERT_TRUE(stateH.isSameShape(results.at(3)));
  ASSERT_TRUE(stateH.equalsTo(results.at(3)));

  results = op.evaluate({&grad, &stateV, &stateM, &stateH}, {0.001f, 0.9f, 0.999f, 1.0e-8}, {});

  NDArray update2C(
      'c', {1, 5},
      {0.00156540157923389, 0.00156540172220632, 0.0015654017698638, 0.00156540179369254, 0.00156540180798979},
      DataType::FLOAT32);
  NDArray stateV2C('c', {1, 5},
                   {0.002997001, 0.01198800400000001, 0.02697300900000002, 0.04795201600000004, 0.07492502500000006},
                   DataType::FLOAT32);
  NDArray stateM2C('c', {1, 5},
                   {0.2709999999999999, 0.5419999999999998, 0.8129999999999998, 1.0839999999999996, 1.3549999999999995},
                   DataType::FLOAT32);
  NDArray stateH2C('c', {1, 5},
                   {0.002997001, 0.01198800400000001, 0.02697300900000002, 0.04795201600000004, 0.07492502500000006},
                   DataType::FLOAT32);

  update.assign(update2C);
  stateV.assign(stateV2C);
  stateM.assign(stateM2C);
  stateH.assign(stateH2C);

  ASSERT_EQ(sd::Status::OK, results.status());

  ASSERT_TRUE(update.isSameShape(results.at(0)));
  ASSERT_TRUE(update.equalsTo(results.at(0)));
  ASSERT_TRUE(stateV.isSameShape(results.at(1)));
  ASSERT_TRUE(stateV.equalsTo(results.at(1)));
  ASSERT_TRUE(stateM.isSameShape(results.at(2)));
  ASSERT_TRUE(stateM.equalsTo(results.at(2)));
  ASSERT_TRUE(stateH.isSameShape(results.at(3)));
  ASSERT_TRUE(stateH.equalsTo(results.at(3)));
}
