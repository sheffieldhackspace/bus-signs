"""A simple web server"""

from micropyserver import MicroPyServer
import utils


def hello_world(request):
    """request handler"""
    print("new request!")
    print(request)
    query_params = utils.get_request_query_params(request)
    print(query_params)
    utils.send_response(server, "Hiya!")


server = MicroPyServer()
server.add_route("/", hello_world)
server.start()
