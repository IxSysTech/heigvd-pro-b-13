--
-- PostgreSQL database dump
--

-- Dumped from database version 11.2
-- Dumped by pg_dump version 11.2

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: PRO19; Type: SCHEMA; Schema: -; Owner: postgres
--

CREATE SCHEMA "PRO19";


ALTER SCHEMA "PRO19" OWNER TO postgres;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: location; Type: TABLE; Schema: PRO19; Owner: postgres
--

CREATE TABLE "PRO19".location (
    id integer NOT NULL,
    goid text NOT NULL,
    name text NOT NULL
);


ALTER TABLE "PRO19".location OWNER TO postgres;

--
-- Name: prot_to_loc; Type: TABLE; Schema: PRO19; Owner: postgres
--

CREATE TABLE "PRO19".prot_to_loc (
    fk_prot integer NOT NULL,
    fk_loc integer NOT NULL
);


ALTER TABLE "PRO19".prot_to_loc OWNER TO postgres;

--
-- Name: prot_to_type; Type: TABLE; Schema: PRO19; Owner: postgres
--

CREATE TABLE "PRO19".prot_to_type (
    fk_prot integer NOT NULL,
    fk_type integer NOT NULL
);


ALTER TABLE "PRO19".prot_to_type OWNER TO postgres;

--
-- Name: protein; Type: TABLE; Schema: PRO19; Owner: postgres
--

CREATE TABLE "PRO19".protein (
    id integer NOT NULL,
    sadn text NOT NULL,
    sprt text NOT NULL
);


ALTER TABLE "PRO19".protein OWNER TO postgres;

--
-- Name: typeOrganism; Type: TABLE; Schema: PRO19; Owner: postgres
--

CREATE TABLE "PRO19"."typeOrganism" (
    id integer NOT NULL,
    name text NOT NULL
);


ALTER TABLE "PRO19"."typeOrganism" OWNER TO postgres;

--
-- Name: location location_pkey; Type: CONSTRAINT; Schema: PRO19; Owner: postgres
--

ALTER TABLE ONLY "PRO19".location
    ADD CONSTRAINT location_pkey PRIMARY KEY (id);


--
-- Name: prot_to_loc pr_prot-loc; Type: CONSTRAINT; Schema: PRO19; Owner: postgres
--

ALTER TABLE ONLY "PRO19".prot_to_loc
    ADD CONSTRAINT "pr_prot-loc" PRIMARY KEY (fk_prot, fk_loc);


--
-- Name: prot_to_type pr_prot-type; Type: CONSTRAINT; Schema: PRO19; Owner: postgres
--

ALTER TABLE ONLY "PRO19".prot_to_type
    ADD CONSTRAINT "pr_prot-type" PRIMARY KEY (fk_prot, fk_type);


--
-- Name: protein protein_pkey; Type: CONSTRAINT; Schema: PRO19; Owner: postgres
--

ALTER TABLE ONLY "PRO19".protein
    ADD CONSTRAINT protein_pkey PRIMARY KEY (id);


--
-- Name: typeOrganism type_pkey; Type: CONSTRAINT; Schema: PRO19; Owner: postgres
--

ALTER TABLE ONLY "PRO19"."typeOrganism"
    ADD CONSTRAINT type_pkey PRIMARY KEY (id);


--
-- Name: prot_to_loc fk_loc; Type: FK CONSTRAINT; Schema: PRO19; Owner: postgres
--

ALTER TABLE ONLY "PRO19".prot_to_loc
    ADD CONSTRAINT fk_loc FOREIGN KEY (fk_prot) REFERENCES "PRO19".location(id);


--
-- Name: prot_to_type fk_prot; Type: FK CONSTRAINT; Schema: PRO19; Owner: postgres
--

ALTER TABLE ONLY "PRO19".prot_to_type
    ADD CONSTRAINT fk_prot FOREIGN KEY (fk_prot) REFERENCES "PRO19".protein(id);


--
-- Name: prot_to_loc fk_prot; Type: FK CONSTRAINT; Schema: PRO19; Owner: postgres
--

ALTER TABLE ONLY "PRO19".prot_to_loc
    ADD CONSTRAINT fk_prot FOREIGN KEY (fk_prot) REFERENCES "PRO19".protein(id);


--
-- Name: prot_to_type fk_type; Type: FK CONSTRAINT; Schema: PRO19; Owner: postgres
--

ALTER TABLE ONLY "PRO19".prot_to_type
    ADD CONSTRAINT fk_type FOREIGN KEY (fk_type) REFERENCES "PRO19"."typeOrganism"(id);


--
-- PostgreSQL database dump complete
--

