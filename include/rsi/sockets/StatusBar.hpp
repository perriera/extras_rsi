// #ifndef _EXPARX_RSISTATUSBAR_HPP
// #define _EXPARX_RSISTATUSBAR_HPP

// #include <extras/interfaces.hpp>
// #include <rsi/sockets/Types.hpp>
// #include <iostream>
// #include <rsi/exceptions.hpp>

// namespace extras {
//     namespace rsi {

//         /**
//          * @brief BurstInterface
//          *
//          */

//         using StatusBarMsg = std::string;

//         interface StatusBarInterface {

//             virtual StatusMsg start(const StatusMsg& msg) const pure;
//             virtual StatusMsg pass(const StatusMsg& msg) const pure;
//             virtual StatusMsg fail(const StatusMsg& msg) const pure;
//             virtual StatusMsg end(const StatusMsg& msg) const pure;

//         };

//         concrete class StatusBar implements StatusBarInterface {
//         public:

//             virtual StatusMsg start(const StatusMsg& msg) const override;
//             virtual StatusMsg pass(const StatusMsg& msg) const override;
//             virtual StatusMsg fail(const StatusMsg& msg) const override;
//             virtual StatusMsg end(const StatusMsg& msg) const override;

//         };

//         /**
//          * @brief start std::ostream& manipulator
//          *
//          */
//         class start
//         {
//             friend std::ostream& operator<<(std::ostream& out, const start& obj) {
//                 out << StatusLine().start(obj._msg);
//                 return out;
//             }
//         public:
//             start(const StatusMsg& msg) : _msg(msg) {}
//             std::ostream& operator()(std::ostream& out) const {
//                 out << StatusLine().start(_msg);
//                 return out;
//             }
//         private:
//             StatusMsg _msg;
//         };

//         /**
//          * @brief pass std::ostream& manipulator
//          *
//          */
//         class pass
//         {
//             friend std::ostream& operator<<(std::ostream& out, const pass& obj) {
//                 out << StatusLine().pass(obj._msg);
//                 return out;
//             }
//         public:
//             pass(const StatusMsg& msg) : _msg(msg) {}
//             std::ostream& operator()(std::ostream& out) const {
//                 out << StatusLine().pass(_msg);
//                 return out;
//             }
//         private:
//             StatusMsg _msg;
//         };

//         /**
//          * @brief fail std::ostream& manipulator
//          *
//          */
//         class fail
//         {
//             friend std::ostream& operator<<(std::ostream& out, const fail& obj) {
//                 out << StatusLine().pass(obj._msg);
//                 return out;
//             }
//         public:
//             fail(const StatusMsg& msg) : _msg(msg) {}
//             std::ostream& operator()(std::ostream& out) const {
//                 out << StatusLine().fail(_msg);
//                 return out;
//             }
//         private:
//             StatusMsg _msg;
//         };

//         /**
//          * @brief start std::ostream& manipulator
//          *
//          */
//         class end
//         {
//             friend std::ostream& operator<<(std::ostream& out, const end& obj) {
//                 out << StatusLine().end(obj._msg);
//                 return out;
//             }
//         public:
//             end(const StatusMsg& msg) : _msg(msg) {}
//             std::ostream& operator()(std::ostream& out) const {
//                 out << StatusLine().start(_msg);
//                 return out;
//             }
//         private:
//             StatusMsg _msg;
//         };


//         /**
//          * @brief PackedException
//          *
//          */
//         concrete class StatusLineException extends RSIException {
//         public:
//             StatusLineException(std::string msg, const extras::WhereAmI& whereAmI)
//                 : RSIException(msg.c_str(), whereAmI) {}
//             static void assertion(int status, const extras::WhereAmI& ref);
//         };

//     }
// }

// #endif // _EXPARX_RSISTATUSBAR_HPP


